#include "VarifyGrpcClient.h"
#include "ConfigMgr.h"
RPCConPool::RPCConPool(std::size_t size, std::string host, std::string port):_pool_size(size)
{
	std::shared_ptr<Channel> channel = grpc::CreateChannel(host+":"+port,
		grpc::InsecureChannelCredentials());
	for (std::size_t i = 0;i < _pool_size; i++) {
		_stub_queue.push(VarifyService::NewStub(channel));
	}
}

RPCConPool::~RPCConPool()
{
	std::lock_guard<std::mutex> lock(_mutex);
	_b_stop = true; //表示回收
	_cond.notify_all(); //通知所有挂起的线程
	while (!_stub_queue.empty()) {
		_stub_queue.pop();
	}
}

std::unique_ptr<VarifyService::Stub> RPCConPool::GetStub()
{
	std::unique_lock<std::mutex> lock(_mutex); //unique_lock可以手动释放锁，而条件变量需要释放锁
	_cond.wait(lock, [this]() {
		if (_b_stop) {
			return true;
		}
		return !_stub_queue.empty(); //只有queue不为空才不会挂起
		});
	if (_b_stop) { //表示已经开始回收
		return nullptr;
	}
	std::unique_ptr<VarifyService::Stub> newStub = std::move(_stub_queue.front());
	_stub_queue.pop();
	return newStub;
}

void RPCConPool::ReturnStub(std::unique_ptr<VarifyService::Stub> returnStub)
{
	std::lock_guard<std::mutex> lock(_mutex);
	if (_b_stop) {
		return;
	}
	_stub_queue.push(std::move(returnStub));
	_cond.notify_one(); //拥有了一个stub就可以释放一个进程
}

VarifyGrpcClient::VarifyGrpcClient()
{
	auto& configMgr = ConfigMgr::Inst();
	std::string host = configMgr["VarifyServer"]["host"];
	std::string port = configMgr["VarifyServer"]["port"];
	_pool.reset(new RPCConPool(5, host, port));

}

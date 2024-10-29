#pragma once
#include <grpcpp/grpcpp.h>
#include "../message.grpc.pb.h"
#include "const.h"
#include "Singleton.h"
#include <queue>
using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetVarifyReq;
using message::GetVarifyRsp;
using message::VarifyService;

class RPCConPool { //实现stub的并发
public:
	RPCConPool(std::size_t size, std::string host, std::string port);
	~RPCConPool();
	std::unique_ptr<VarifyService::Stub> GetStub(); //必须返回引用
	void ReturnStub(std::unique_ptr<VarifyService::Stub> returnStub);
private:
	std::size_t _pool_size;
	std::mutex _mutex;
	std::condition_variable _cond;
	std::queue<unique_ptr< VarifyService::Stub>> _stub_queue;
	atomic<bool> _b_stop; //感觉可以不用atomic
};
class VarifyGrpcClient :public Singleton<VarifyGrpcClient>
{
	friend class Singleton;
public:
	GetVarifyRsp GetVarifyCode(std::string email) {
		ClientContext context;
		GetVarifyReq request;
		GetVarifyRsp response;
		request.set_email(email);
		std::unique_ptr<VarifyService::Stub> stub = _pool->GetStub();
		Status status = stub->GetVarifyCode(&context, request, &response);
		if (!status.ok()) {
			std::cerr << "获取验证码失败" << std::endl;
			response.set_error(ErrorCodes::RPCFailed);
		}
		_pool->ReturnStub(std::move(stub));
		return response;

	}

private:
	VarifyGrpcClient();
	std::unique_ptr<VarifyService::Stub> _stub;
	std::unique_ptr<RPCConPool> _pool;
};
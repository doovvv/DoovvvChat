#include "CServer.h"
#include "HttpConnection.h"
#include "AsioIOContextPool.h"
CServer::CServer(net::io_context& ioc, unsigned short& port):_ioc(ioc),_acceptor(ioc,tcp::endpoint(tcp::v4(),port)),
_socket(ioc) {

}
void CServer::Start() {
	auto self = shared_from_this();//防止回调函数还没回调对象已经被析构
	auto& ioc = AsioIOContextPool::GetInstance()->GetIOContext(); //从连接池中取出一个iocontext，用来http收发	
	std::shared_ptr<HttpConnection> newCon = std::make_shared<HttpConnection>(ioc); //创建一个连接
	boost::asio::ip::tcp::socket& socket = newCon->GetSocket(); //得到该连接的socket
	_acceptor.async_accept(socket, [self,newCon](beast::error_code ec) { //连接到客户端，此时socket与用户才建立上连接
		try {
			//出错，放弃连接，继续监听其他连接
			if (ec) {
				self->Start();
				return;
			}
			//启动连接管理
			//socket不允许拷贝赋值
			newCon->Start();
			//继续监听，每次调用的Start()会使用不同的iocontext，而iocontext又是跑在不同的线程中的
			self->Start();
		}
		catch (std::exception& exp) {

		}

		});
}

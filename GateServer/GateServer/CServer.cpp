#include "CServer.h"
#include "HttpConnection.h"
CServer::CServer(net::io_context& ioc, unsigned short& port):_ioc(ioc),_acceptor(ioc,tcp::endpoint(tcp::v4(),port)),
_socket(ioc) {

}
void CServer::Start() {
	auto self = shared_from_this();//防止回调还没回调对象已经被析构
	_acceptor.async_accept(_socket, [self](beast::error_code ec) {
		try {
			//出错，放弃连接，继续监听其他连接
			if (ec) {
				self->Start();
				return;
			}
			//启动连接管理
			//socket不允许拷贝赋值
			std::make_shared<HttpConnection>(std::move(self->_socket))->Start();
			//继续监听
			self->Start();
		}
		catch (std::exception& exp) {

		}

		});
}

#include "CServer.h"
#include "HttpConnection.h"
#include "AsioIOContextPool.h"
CServer::CServer(net::io_context& ioc, unsigned short& port):_ioc(ioc),_acceptor(ioc,tcp::endpoint(tcp::v4(),port)),
_socket(ioc) {

}
void CServer::Start() {
	auto self = shared_from_this();//��ֹ�ص���û�ص������Ѿ�������
	auto& ioc = AsioIOContextPool::GetInstance()->GetIOContext(); //�����ӳ���ȡ��һ��iocontext������http�շ�	
	std::shared_ptr<HttpConnection> newCon = std::make_shared<HttpConnection>(ioc);
	boost::asio::ip::tcp::socket& socket = newCon->GetSocket();
	_acceptor.async_accept(socket, [self,newCon](beast::error_code ec) {
		try {
			//�������������ӣ�����������������
			if (ec) {
				self->Start();
				return;
			}
			//�������ӹ���
			//socket������������ֵ
			newCon->Start();
			//����������ÿ�ε��õ�Start()��ʹ�ò�ͬ��iocontext����iocontext�������ڲ�ͬ���߳��е�
			self->Start();
		}
		catch (std::exception& exp) {

		}

		});
}
#pragma once
#include "const.h"
class CServer:public std::enable_shared_from_this<CServer>
{
public:
	//ioc������һ�����������ײ��һֱ��ѯ�����ж��¼�������֪ͨ�ϲ�ص�����
	CServer(net::io_context & ioc, unsigned short& port);
	void Start();
private:
	tcp::acceptor _acceptor;//��Ҫ�󶨵�����
	tcp::socket _socket;
	net::io_context& _ioc;//�������ͣ�û�п������ƣ�ֻ��һ��ʵ������ֻ���ڳ�ʼ���б������ʼ��
};
#pragma once
#include "const.h"
class CServer:public std::enable_shared_from_this<CServer>
{
public:
	//ioc类似于一个调度器，底层会一直轮询，若有读事件发生会通知上层回调函数
	CServer(net::io_context & ioc, unsigned short& port);
	void Start();
private:
	tcp::acceptor _acceptor;//需要绑定调度器
	tcp::socket _socket;
	net::io_context& _ioc;//引用类型（没有拷贝复制，只有一个实例），只能在初始化列表里面初始化
};

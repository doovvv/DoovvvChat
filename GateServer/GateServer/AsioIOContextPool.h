#pragma once
#include "const.h"
using IOContext = boost::asio::io_context;
class AsioIOContextPool:public Singleton<AsioIOContextPool>
{
	friend class Singleton;
public:
	~AsioIOContextPool();
	IOContext& GetIOContext();
private:
	void Stop();
	AsioIOContextPool(std::size_t size = std::thread::hardware_concurrency());
	std::vector<IOContext> _io_contexts;
	std::vector<std::unique_ptr<IOContext::work>> _works; //��ֹio_context.run()��û��io����ʱ�˳�
	std::size_t _next_iocontext;
	std::vector<std::thread> _threads;
};

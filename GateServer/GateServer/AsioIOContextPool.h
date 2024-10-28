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
	std::vector<std::unique_ptr<IOContext::work>> _works; //防止io_context.run()在没有io请求时退出
	std::size_t _next_iocontext;
	std::vector<std::thread> _threads;
};


#include "AsioIOContextPool.h"

AsioIOContextPool::~AsioIOContextPool()
{
	Stop();
	std::cout << "AsioIOServicePool destruct" << endl;
}

IOContext& AsioIOContextPool::GetIOContext()
{
	auto& context = _io_contexts[_next_iocontext];
	_next_iocontext = (_next_iocontext + 1) % _io_contexts.size(); //һֱ��ѯ��ȡ����Ӧ��iocontext
	return context;
}

void AsioIOContextPool::Stop()
{
	for (auto& work : _works) {
		work->get_io_context().stop();
		work.reset(); //��������ָ��ĳ�Ա����������->. reset֮��iocontext.run()�Ż᷵��
	}
	for (auto& t : _threads) {
		t.join(); //�˳��߳�
	}
}

AsioIOContextPool::AsioIOContextPool(std::size_t size):_io_contexts(size),_works(size), _next_iocontext(0)
{
	for (std::size_t i = 0;i < size;i++) {
		_works[i] = make_unique<IOContext::work>(_io_contexts[i]);
	}
	for (size_t i = 0; i < size; i++)
	{
		_threads.emplace_back(std::thread([this, i]() {
			_io_contexts[i].run();
			}));
	}
}
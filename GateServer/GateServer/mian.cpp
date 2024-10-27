#include "CServer.h"
#include "ConfigMgr.h"
int main() {
	ConfigMgr configMgr;
	std::string port_string = configMgr["GateServer"]["Port"];
	unsigned short port = atoi(port_string.c_str());
	try
	{
		net::io_context ioc{ 1 };
		boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
		signals.async_wait([&ioc](boost::system::error_code ec, int) {
			if (ec) {
				std::cerr << "Error:" << ec.what() << std::endl;
				return;
			}
			ioc.stop();
			});
		std::make_shared<CServer>(ioc, port)->Start();
		std::cout << "Gate Server is running on " << port << std::endl;
		ioc.run(); //×èÈûµÄ
	}
	catch (const std::exception& exp)
	{
		std::cerr << "Error:" << exp.what() << std::endl;
	}
	return 0;
}
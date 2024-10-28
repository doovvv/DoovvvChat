#pragma once
#include "const.h"
class HttpConnection :public std::enable_shared_from_this<HttpConnection> {
	friend class LogicSystem;
public:
	HttpConnection(boost::asio::io_context& ioc); //如果 io_context 支持拷贝构造，那么两个 io_context 对象可能会试图同时控制同一组底层资源，这会导致资源的双重释放或未定义的行为。
	void Start();
	boost::asio::ip::tcp::socket& GetSocket();
private:
	void CheckDeadline();
	void WriteResponse();
	void HandleReq();
	void PreParseGetParam();
	tcp::socket _socket;
	beast::flat_buffer _buffer{ 8192 };
	http::request<http::dynamic_body> _request;
	http::response<http::dynamic_body> _response;
	net::steady_timer _deadline{
		_socket.get_executor(),std::chrono::seconds(60)
	};
	std::string _get_url;
	std::unordered_map<std::string, std::string> _get_params;
};
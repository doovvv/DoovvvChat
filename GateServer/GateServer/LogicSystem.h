#pragma once
#include "const.h"
class HttpConnection;//∑¿÷πª•“˝”√
typedef std::function<void(std::shared_ptr<HttpConnection>)> HttpHandler;
class LogicSystem :public Singleton<LogicSystem> {
	friend class Singleton;
public:
	LogicSystem();
	void ReqGet(std::string url, HttpHandler handler);
	void ReqPost(std::string url, HttpHandler handler);
	bool HandleReq(std::string url, std::shared_ptr<HttpConnection>);
	bool HandlePost(std::string url, std::shared_ptr<HttpConnection>);
private:
	std::map<std::string, HttpHandler> _get_handlers;
	std::map<std::string, HttpHandler> _post_handlers;
};
#pragma once
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <memory>
#include <iostream>
#include <functional>
#include "Singleton.h"
#include <map>
#include <unordered_map>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#define CODEPREFIX "code_"
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

enum ErrorCodes {
	Success = 0,
	ErrorJson = 1001,
	RPCFailed = 1002,
	VarifyExpired =1003,
	VarifyCodeErr = 1004,
	UserExisted = 1005
};
//自己封装的Defer类
class Defer {
public:
	Defer(std::function<void()> func) :_func(func) {}
	~Defer() {
		_func();
	}
private:
	std::function<void()> _func;
};
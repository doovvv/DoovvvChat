#include "HttpConnection.h"
#include "LogicSystem.h"
#include "VarifyGrpcClient.h"
#include "RedisMgr.h"
void LogicSystem::ReqGet(std::string url, HttpHandler handler) {
	_get_handlers.insert(make_pair(url, handler));
}
void LogicSystem::ReqPost(std::string url, HttpHandler handler) {
	_post_handlers.insert(make_pair(url, handler));
}
bool LogicSystem::HandleReq(std::string url,std::shared_ptr<HttpConnection> con) {
	if (_get_handlers.find(url) == _get_handlers.end()) {
		return false;
	}
	_get_handlers[url](con);
	return true;
}
bool LogicSystem::HandlePost(std::string url, std::shared_ptr<HttpConnection> con) {
	if (_post_handlers.find(url) == _post_handlers.end()) {
		return false;
	}
	_post_handlers[url](con);
	return true;
}
LogicSystem::LogicSystem() {
	ReqGet("/get-test", [](std::shared_ptr<HttpConnection> con) {
		beast::ostream(con->_response.body()) << "receive get-test req\r\n";
		});
	ReqPost("/get_varifycode", [](std::shared_ptr<HttpConnection> con) {
		auto body_str = boost::beast::buffers_to_string(con->_request.body().data()); //_request是http::request类型
		con->_response.set(http::field::content_type, "text/json");
		Json::Reader reader;
		Json::Value root; //response
		Json::Value src_root; //request
		std::cout << "body_str is " << body_str << std::endl;
		bool success = reader.parse(body_str, src_root);
		if (!success) { //解析失败的情况
			std::cerr << "json parse error is" << reader.getFormatedErrorMessages()<<std::endl;
			root["error"] = ErrorJson;
			std::string json_str = root.toStyledString();
			beast::ostream(con->_response.body()) << json_str;
			return false;
		}
		if(!src_root.isMember("email")) { //email不存在
			std::cerr << "no email" << std::endl;
			root["error"] = ErrorJson;
			std::string json_str = root.toStyledString();
			beast::ostream(con->_response.body()) << json_str;
			return false;
		}
		GetVarifyRsp response = VarifyGrpcClient::GetInstance()->GetVarifyCode(src_root["email"].asString()); //rpc
		root["error"] = response.error();
		root["email"] = src_root["email"];
		std::string json_str = root.toStyledString();
		beast::ostream(con->_response.body()) << json_str;
		});
	ReqPost("/user_register", [](std::shared_ptr<HttpConnection> con) {
		auto body_str = boost::beast::buffers_to_string(con->_request.body().data()); //_request是http::request类型
		con->_response.set(http::field::content_type, "text/json");
		Json::Reader reader;
		Json::Value root; //response
		Json::Value src_root; //request
		std::cout << "body_str is " << body_str << std::endl;
		bool success = reader.parse(body_str, src_root); //解析成json格式
		if (!success) { //解析失败的情况
			std::cerr << "json parse error is" << reader.getFormatedErrorMessages() << std::endl;
			root["error"] = ErrorJson;
			std::string json_str = root.toStyledString();
			beast::ostream(con->_response.body()) << json_str;
			return false;
		}
		std::string varify_code;
		bool b_get_varify = RedisMgr::GetInstance()->Get(CODEPREFIX+src_root["email"].asString(), varify_code);//在redis中查询验证码
		if (!b_get_varify) { //验证码不存在（过期）
			std::cout << " get varify code expired" << std::endl;
			root["error"] = ErrorCodes::VarifyExpired;
			std::string jsonstr = root.toStyledString();
			beast::ostream(con->_response.body()) << jsonstr;
			return true;
		}
		if (varify_code != src_root["varifycode"].asString()) { //验证码不正确
			std::cout << " varify code error,true varify_code is " <<varify_code<<
				"but recive "<< src_root["varifycode"].asString()<< std::endl;
			root["error"] = ErrorCodes::VarifyCodeErr;
			std::string jsonstr = root.toStyledString();
			beast::ostream(con->_response.body()) << jsonstr;
			return true;
		}
		root["error"] = 0;
		root["email"] = src_root["email"];
		root["user"] = src_root["user"].asString();
		root["passwd"] = src_root["passwd"].asString();
		root["confirm"] = src_root["confirm"].asString();
		root["varifycode"] = src_root["varifycode"].asString();
		std::string jsonstr = root.toStyledString();
		beast::ostream(con->_response.body()) << jsonstr;
		return true;
		});
}
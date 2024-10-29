#include "HttpConnection.h"
#include "LogicSystem.h"
#include "VarifyGrpcClient.h"
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
		auto body_str = boost::beast::buffers_to_string(con->_request.body().data());
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
}
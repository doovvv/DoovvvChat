#pragma once
#include <grpcpp/grpcpp.h>
#include "../message.grpc.pb.h"
#include "const.h"
#include "Singleton.h"
using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetVarifyReq;
using message::GetVarifyRsp;
using message::VarifyService;
class VarifyGrpcClient :public Singleton<VarifyGrpcClient>
{
	friend class Singleton;
public:
	GetVarifyRsp GetVarifyCode(std::string email) {
		ClientContext context;
		GetVarifyReq request;
		GetVarifyRsp response;
		request.set_email(email);

		Status status = _stub->GetVarifyCode(&context, request, &response);
		if(!status.ok()){
			std::cerr << "获取验证码失败" << std::endl;
			response.set_error(ErrorCodes::RPCFailed);
		}
		return response;

	}
	
private:
	VarifyGrpcClient() {
		std::shared_ptr<Channel> channel = grpc::CreateChannel("127.0.0.1:50051",
			grpc::InsecureChannelCredentials());
		_stub = VarifyService::NewStub(channel);
	}
	std::shared_ptr<VarifyService::Stub> _stub;

};
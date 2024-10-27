#include "httpmgr.h"

HttpMgr::~HttpMgr()
{

}

HttpMgr::HttpMgr()
{
    connect(this,&HttpMgr::SigHttpFinish,this,&HttpMgr::SlotHttpFinish);
}

void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId reqId, Modules mod)
{
    QByteArray data = QJsonDocument(json).toJson();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"text/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(data.length()));
    auto self = shared_from_this(); //由this指针得到的智能对象
    QNetworkReply* reply = _manager.post(request,data);
    connect(reply,&QNetworkReply::finished,[self,reply,reqId,mod](){
        if(reply->error() != QNetworkReply::NoError){
            qDebug()<<reply->errorString();
            emit self->SigHttpFinish(reqId,"",ErrorCodes::ERR_NETWORK,mod);
            reply->deleteLater();
        }
        QString res = reply->readAll();
        qDebug()<<"res is"<<res;
        emit self->SigHttpFinish(reqId,res,ErrorCodes::SUCCESS,mod);
        reply->deleteLater();
    });
}

void HttpMgr::SlotHttpFinish(ReqId reqId, QString res, ErrorCodes err, Modules mod)
{
    if(mod == Modules::REGISTERMOD){
        emit SigRegModFinish(reqId,res,err);
    }
}

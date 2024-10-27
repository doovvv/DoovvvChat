#ifndef HTTPMGR_H
#define HTTPMGR_H
#include "Singleton.h"

class HttpMgr:public QObject, public Singleton<HttpMgr>,public std::enable_shared_from_this<HttpMgr>
{
     Q_OBJECT
public:
    ~HttpMgr();
    void PostHttpReq(QUrl url,QJsonObject json, ReqId reqId, Modules mod);
private:
    QNetworkAccessManager _manager;
    friend class Singleton<HttpMgr>;//使得基类可以使用HttpMgr的构建函数
    HttpMgr();
signals:
    void SigHttpFinish(ReqId reqId,QString  res,ErrorCodes err, Modules mod);
    void SigRegModFinish(ReqId reqId,QString  res,ErrorCodes err);
private slots:
    void SlotHttpFinish(ReqId reqId,QString  res,ErrorCodes err, Modules mod);
};

#endif // HTTPMGR_H

#ifndef GLOBAL_H
#define GLOBAL_H
#include <QWidget>
#include <functional>
#include <QStyle>
#include <mutex>
#include <iostream>
#include <QUrl>
#include <QJsonObject>
#include <QByteArray>
#include <QJsonDocument>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QDir>
#include <QSettings>
extern std::function<void(QWidget*)> repolish;

enum ReqId{
    ID_GET_VARIFY_CODE = 1001,//获取验证码
    ID_REG_USER = 1002,//注册用户
};
enum Modules{
    REGISTERMOD = 0,//注册模块
};
enum ErrorCodes{
    SUCCESS = 0,
    ERR_JSON = 1,//json解析失败
    ERR_NETWORK = 2,//网络错误
    ErrorJson = 1001,
    RPCFailed = 1002,
    VarifyExpired =1003,
    VarifyCodeErr = 1004
};
extern QString gate_url_prefix;
#endif // GLOBAL_H

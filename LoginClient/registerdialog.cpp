#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"
#include <QRegularExpression>
#include "httpmgr.h"
RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    //初始化handlers
    InitHandlers();
    //将密码框设置为密码模式
    ui->setupUi(this);
    ui->passLineEdit->setEchoMode(QLineEdit::Password);
    ui->verifyLineEdit->setEchoMode(QLineEdit::Password);

    //设置提示的初始状态
    ui->errorTipLabel->setProperty("state","normal");
    repolish(this);

    //连接http完成发送
    connect(HttpMgr::GetInstance().get(),&HttpMgr::SigRegModFinish,this,&RegisterDialog::SlotRegModFinish);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_getCodeBtn_clicked()
{
    //验证邮箱的地址正则表达式
    auto email = ui->emailLineEdit->text();
    // 邮箱地址的正则表达式
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch(); // 执行正则表达式匹配
    if(match){
        //发送http请求获取验证码
        QJsonObject json_obj;
        json_obj["email"] = email;
        HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix+"/get_varifycode"),
                                            json_obj, ReqId::ID_GET_VARIFY_CODE,Modules::REGISTERMOD);

    }else{
        //提示邮箱不正确
        ShowTip(tr("邮箱地址不正确"),false);
    }
}

void RegisterDialog::SlotRegModFinish(ReqId reqId, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS){
        ShowTip("网络错误",false);
        return;
    }
    QJsonDocument json = QJsonDocument::fromJson(res.toUtf8());
    if(json.isNull()){
        qDebug()<<res;
        ShowTip("json解析错误，json is null",false);
        return;
    }
    if(!json.isObject()){
        ShowTip("json解析错误",false);
        return;
    }
    QJsonObject jsonObj = json.object();
    qDebug()<<"成功解析json";
    _handlers[reqId](jsonObj);

}

void RegisterDialog::ShowTip(QString str,bool state)
{
    if(state){
        ui->errorTipLabel->setProperty("state","normal");
    }
    else{
        ui->errorTipLabel->setProperty("state","err");
    }
    ui->errorTipLabel->setText(str);
    repolish(ui->errorTipLabel);
}

void RegisterDialog::InitHandlers()
{
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE,[this](const QJsonObject& jsonObj){
        qDebug()<<"开始处理\n";
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            ShowTip("验证码发送错误",false);
            return;
        }
        QString email = jsonObj["email"].toString();
        ShowTip("验证码已经发送到你的邮箱，请注意查收",true);
        qDebug()<<"email is "<<email;
    });
}


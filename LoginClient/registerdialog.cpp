#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"
#include <QRegularExpression>
#include "httpmgr.h"
RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog),_count(5)
{
    ui->setupUi(this);
    //初始化handlers
    InitHandlers();
    //将密码框设置为密码模式
    ui->passLineEdit->setEchoMode(QLineEdit::Password);
    ui->verifyLineEdit->setEchoMode(QLineEdit::Password);

    //设置提示的初始状态
    ui->errorTipLabel->setProperty("state","normal");
    repolish(this);

    //连接http完成发送
    connect(HttpMgr::GetInstance().get(),&HttpMgr::SigRegModFinish,this,&RegisterDialog::SlotRegModFinish);

    connect(ui->userLineEdit,&QLineEdit::editingFinished,this,[this](){
        checkUserValid();
    });
    connect(ui->emailLineEdit, &QLineEdit::editingFinished, this, [this](){
        checkEmailValid();
    });
    connect(ui->passLineEdit, &QLineEdit::editingFinished, this, [this](){
        checkPassValid();
    });
    connect(ui->verifyLineEdit, &QLineEdit::editingFinished, this, [this](){
        checkConfirmValid();
    });
    connect(ui->checkLineEdit, &QLineEdit::editingFinished, this, [this](){
        checkVarifyValid();
    });
    //初始化计时器
    _return_timer = new QTimer(this);
    connect(_return_timer, &QTimer::timeout, [this](){
        if(_count==0){
            _return_timer->stop();
            emit sigSwitchLogin();
            return;
        }
        _count--;
        auto str = QString("注册成功，%1 s后返回登录").arg(_count);
        ui->tipLabel->setText(str);
    });
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
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            ShowTip("验证码发送错误",false);
            return;
        }
        QString email = jsonObj["email"].toString();
        ShowTip("验证码已经发送到你的邮箱，请注意查收",true);
        qDebug()<<"email is "<<email;
    });
    _handlers.insert(ReqId::ID_REG_USER,[this](const QJsonObject& jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            ShowTip("注册错误",false);
            return;
        }
        ShowTip("注册成功！",true);
        ChangeTipPage();
    });
}

void RegisterDialog::AddTipErr(TipErr te, QString tips)
{
    _tip_errs[te] = tips;
    ShowTip(tips, false);
}

void RegisterDialog::DelTipErr(TipErr te)
{
    _tip_errs.remove(te);
    if(_tip_errs.empty()){
        ui->errorTipLabel->clear();
        return;
    }
    ShowTip(_tip_errs.first(), false);
}

bool RegisterDialog::checkUserValid()
{
    if(ui->userLineEdit->text() == ""){
        AddTipErr(TipErr::TIP_USER_ERR, tr("用户名不能为空"));
        return false;
    }
    DelTipErr(TipErr::TIP_USER_ERR);
    return true;
}

bool RegisterDialog::checkPassValid()
{
    auto pass = ui->passLineEdit->text();
    if(pass.length() < 6 || pass.length()>15){
        //提示长度不准确
        AddTipErr(TipErr::TIP_PWD_ERR, tr("密码长度应为6~15"));
        return false;
    }
    // 创建一个正则表达式对象，按照上述密码要求
    // 这个正则表达式解释：
    // ^[a-zA-Z0-9!@#$%^&*]{6,15}$ 密码长度至少6，可以是字母、数字和特定的特殊字符
    QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*]{6,15}$");
    bool match = regExp.match(pass).hasMatch();
    if(!match){
        //提示字符非法
        AddTipErr(TipErr::TIP_PWD_ERR, tr("不能包含非法字符"));
        return false;;
    }
    DelTipErr(TipErr::TIP_PWD_ERR);
    return true;
}
bool RegisterDialog::checkEmailValid()
{
    //验证邮箱的地址正则表达式
    auto email = ui->emailLineEdit->text();
    // 邮箱地址的正则表达式
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch(); // 执行正则表达式匹配
    if(!match){
        //提示邮箱不正确
        AddTipErr(TipErr::TIP_EMAIL_ERR, tr("邮箱地址不正确"));
        return false;
    }
    DelTipErr(TipErr::TIP_EMAIL_ERR);
    return true;
}

bool RegisterDialog::checkConfirmValid()
{
    auto pass = ui->passLineEdit->text();
    if(pass.length() < 6 || pass.length()>15){
        //提示长度不准确
        AddTipErr(TipErr::TIP_PWD_ERR, tr("密码长度应为6~15"));
        return false;
    }
    // 创建一个正则表达式对象，按照上述密码要求
    // 这个正则表达式解释：
    // ^[a-zA-Z0-9!@#$%^&*]{6,15}$ 密码长度至少6，可以是字母、数字和特定的特殊字符
    QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*]{6,15}$");
    bool match = regExp.match(pass).hasMatch();
    if(!match){
        //提示字符非法
        AddTipErr(TipErr::TIP_PWD_ERR, tr("不能包含非法字符"));
        return false;;
    }
    DelTipErr(TipErr::TIP_PWD_ERR);
    if(pass != ui->verifyLineEdit->text()){
        AddTipErr(TipErr::TIP_PWD_CONFIRM,tr("确认密码不一致"));
        return false;
    }
    return true;
}

void RegisterDialog::ChangeTipPage()
{
    _return_timer->stop();
    ui->stackedWidget->setCurrentWidget(ui->page_2);
    // 启动定时器，设置间隔为1000毫秒（1秒）
    _return_timer->start(1000);
}
bool RegisterDialog::checkVarifyValid()
{
    auto pass = ui->checkLineEdit->text();
    if(pass.isEmpty()){
        AddTipErr(TipErr::TIP_VARIFY_ERR, tr("验证码不能为空"));
        return false;
    }
    DelTipErr(TipErr::TIP_VARIFY_ERR);
    return true;
}
void RegisterDialog::on_confirmBtn_clicked()
{
    bool valid = checkUserValid();
    if(!valid){
        return;
    }
    valid = checkEmailValid();
    if(!valid){
        return;
    }
    valid = checkPassValid();
    if(!valid){
        return;
    }
    valid = checkVarifyValid();
    if(!valid){
        return;
    }
    QJsonObject json_obj;
    json_obj["user"] = ui->userLineEdit->text();
    json_obj["email"] = ui->emailLineEdit->text();
    json_obj["password"] = XorString(ui->passLineEdit->text());
    json_obj["confirm"] = XorString(ui->verifyLineEdit->text());
    json_obj["varifycode"] = ui->checkLineEdit->text();
    HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix+"/user_register"), //提交注册信息
                                        json_obj, ReqId::ID_REG_USER,Modules::REGISTERMOD);
}


void RegisterDialog::on_returnBtn_clicked()
{
    _return_timer->stop();
    emit sigSwitchLogin();
}


void RegisterDialog::on_cancelBtn_clicked()
{
    _return_timer->stop();
    emit sigSwitchLogin();
}


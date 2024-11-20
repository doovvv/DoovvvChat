/******************************************************************************
 *
 * @file       mainwindow.cpp
 * @brief      主窗口
 *
 * @author     doovvv
 * @date       2024/09/28
 * @history
 *****************************************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _login_dlg = new LoginDialog(this);
    setCentralWidget(_login_dlg);
    _login_dlg->show();
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    connect(_login_dlg,&LoginDialog::SigSwitchReg,this,&MainWindow::SlotSwitchReg);

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::SlotSwitchLogin()
{
    //创建一个CentralWidget, 并将其设置为MainWindow的中心部件
    _login_dlg = new LoginDialog(this);
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(_login_dlg);
    _register_dlg->hide();
    _login_dlg->show();
    //连接登录界面注册信号
    connect(_login_dlg, &LoginDialog::SigSwitchReg, this, &MainWindow::SlotSwitchReg);

}

void MainWindow::SlotSwitchReg()

{
    //连接注册界面返回登录信号
    _register_dlg = new RegisterDialog(this);
    _register_dlg->hide();
    _register_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    connect(_register_dlg, &RegisterDialog::sigSwitchLogin, this, &MainWindow::SlotSwitchLogin);
    setCentralWidget(_register_dlg);
    _login_dlg->hide();
    _register_dlg->show();
}


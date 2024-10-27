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

    _register_dlg = new RegisterDialog(this);
    connect(_login_dlg,&LoginDialog::SigSwitchReg,this,&MainWindow::SlotSwitchReg);
    _register_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::SlotSwitchReg()
{
    setCentralWidget(_register_dlg);
    _login_dlg->hide();
    _register_dlg->show();
}


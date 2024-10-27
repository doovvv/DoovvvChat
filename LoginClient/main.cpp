#include "mainwindow.h"
#include <QFile>
#include <QApplication>
#include "global.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":/style/style.qss");
    if(qss.open(QFile::ReadOnly)){
        qDebug()<<"open qss success";
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }
    else{
        qDebug()<<"open qss failed";
    }
    QString fileName = "config.ini";
    QString applicationPath = QCoreApplication::applicationDirPath();
    QString configPath = QDir::toNativeSeparators(applicationPath+QDir::separator()+fileName);
    QSettings settings(configPath,QSettings::IniFormat);
    QString gateHost = settings.value("GateServer/host").toString();
    QString port = settings.value("GateServer/port").toString();
    gate_url_prefix = "http://"+gateHost+":"+port;
    qDebug()<<gate_url_prefix;
    MainWindow w;
    w.show();
    return a.exec();
}

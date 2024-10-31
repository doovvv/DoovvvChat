#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include "global.h"
namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_getCodeBtn_clicked();
    void SlotRegModFinish(ReqId reqId,QString  res,ErrorCodes err);
    void on_confirmBtn_clicked();

private:
    QMap<ReqId,std::function<void(const QJsonObject&)>> _handlers;
    Ui::RegisterDialog *ui;
    void ShowTip(QString str,bool state);
    void InitHandlers();
};

#endif // REGISTERDIALOG_H

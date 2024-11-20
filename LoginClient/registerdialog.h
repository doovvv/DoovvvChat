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

    void on_returnBtn_clicked();

    void on_cancelBtn_clicked();

private:
    QMap<ReqId,std::function<void(const QJsonObject&)>> _handlers;
    Ui::RegisterDialog *ui;
    void ShowTip(QString str,bool state);
    void InitHandlers();
    QMap<TipErr, QString> _tip_errs;//用来记录每个输入框的错误
    void AddTipErr(TipErr te, QString tips); //增加错误
    void DelTipErr(TipErr te); //删除错误
    bool checkUserValid();
    bool checkPassValid();
    bool checkVarifyValid();
    bool checkEmailValid();
    bool checkConfirmValid();
    void ChangeTipPage();
    QTimer* _return_timer;
    int _count;
signals:
    void sigSwitchLogin();
};

#endif // REGISTERDIALOG_H

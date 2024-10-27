/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *userLabel;
    QLineEdit *userLineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *passLabel;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QLabel *forgetLabel;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *loginBtn;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *regBtn;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(300, 500);
        horizontalLayout = new QHBoxLayout(LoginDialog);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(LoginDialog);
        widget->setObjectName("widget");
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setPixmap(QPixmap(QString::fromUtf8(":/pic/src/chat.svg")));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);


        verticalLayout->addWidget(widget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(5, 5, 5, 5);
        userLabel = new QLabel(LoginDialog);
        userLabel->setObjectName("userLabel");
        userLabel->setMinimumSize(QSize(0, 25));
        userLabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(userLabel);

        userLineEdit = new QLineEdit(LoginDialog);
        userLineEdit->setObjectName("userLineEdit");
        userLineEdit->setMinimumSize(QSize(0, 25));
        userLineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(userLineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        passLabel = new QLabel(LoginDialog);
        passLabel->setObjectName("passLabel");
        passLabel->setMinimumSize(QSize(0, 25));
        passLabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(passLabel);

        lineEdit = new QLineEdit(LoginDialog);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setMinimumSize(QSize(0, 25));
        lineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        forgetLabel = new QLabel(LoginDialog);
        forgetLabel->setObjectName("forgetLabel");

        horizontalLayout_5->addWidget(forgetLabel);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);

        loginBtn = new QPushButton(LoginDialog);
        loginBtn->setObjectName("loginBtn");

        horizontalLayout_6->addWidget(loginBtn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);

        regBtn = new QPushButton(LoginDialog);
        regBtn->setObjectName("regBtn");
        regBtn->setMinimumSize(QSize(0, 0));
        regBtn->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_7->addWidget(regBtn);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_7);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Dialog", nullptr));
        label->setText(QString());
        userLabel->setText(QCoreApplication::translate("LoginDialog", "\347\224\250\346\210\267:", nullptr));
        passLabel->setText(QCoreApplication::translate("LoginDialog", "\345\257\206\347\240\201:", nullptr));
        forgetLabel->setText(QCoreApplication::translate("LoginDialog", "\345\277\230\350\256\260\345\257\206\347\240\201", nullptr));
        loginBtn->setText(QCoreApplication::translate("LoginDialog", "\347\231\273\345\275\225", nullptr));
        regBtn->setText(QCoreApplication::translate("LoginDialog", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H

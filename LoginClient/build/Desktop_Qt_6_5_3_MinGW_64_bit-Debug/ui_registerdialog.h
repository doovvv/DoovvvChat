/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_3;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_9;
    QLabel *errorTipLabel;
    QHBoxLayout *horizontalLayout_2;
    QLabel *userLabel;
    QLineEdit *userLineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *emailLabel;
    QLineEdit *emailLineEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *passLabel;
    QLineEdit *passLineEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *verifyLabel;
    QLineEdit *verifyLineEdit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *checkLabel;
    QLineEdit *checkLineEdit;
    QPushButton *getCodeBtn;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *confirmBtn;
    QPushButton *cancelBtn;
    QSpacerItem *verticalSpacer_2;
    QWidget *page_2;

    void setupUi(QDialog *RegisterDialog)
    {
        if (RegisterDialog->objectName().isEmpty())
            RegisterDialog->setObjectName("RegisterDialog");
        RegisterDialog->resize(397, 441);
        horizontalLayout = new QHBoxLayout(RegisterDialog);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        stackedWidget = new QStackedWidget(RegisterDialog);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        verticalLayout_3 = new QVBoxLayout(page);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        widget = new QWidget(page);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 30));
        widget->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_9 = new QHBoxLayout(widget);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        errorTipLabel = new QLabel(widget);
        errorTipLabel->setObjectName("errorTipLabel");
        errorTipLabel->setMinimumSize(QSize(0, 25));
        errorTipLabel->setMaximumSize(QSize(16777215, 25));
        errorTipLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(errorTipLabel);


        verticalLayout_3->addWidget(widget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        userLabel = new QLabel(page);
        userLabel->setObjectName("userLabel");
        userLabel->setMinimumSize(QSize(0, 25));
        userLabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(userLabel);

        userLineEdit = new QLineEdit(page);
        userLineEdit->setObjectName("userLineEdit");
        userLineEdit->setMinimumSize(QSize(0, 25));
        userLineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(userLineEdit);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        emailLabel = new QLabel(page);
        emailLabel->setObjectName("emailLabel");
        emailLabel->setMinimumSize(QSize(0, 25));
        emailLabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(emailLabel);

        emailLineEdit = new QLineEdit(page);
        emailLineEdit->setObjectName("emailLineEdit");
        emailLineEdit->setMinimumSize(QSize(0, 25));
        emailLineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(emailLineEdit);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        passLabel = new QLabel(page);
        passLabel->setObjectName("passLabel");
        passLabel->setMinimumSize(QSize(0, 25));
        passLabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_4->addWidget(passLabel);

        passLineEdit = new QLineEdit(page);
        passLineEdit->setObjectName("passLineEdit");
        passLineEdit->setMinimumSize(QSize(0, 25));
        passLineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_4->addWidget(passLineEdit);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        verifyLabel = new QLabel(page);
        verifyLabel->setObjectName("verifyLabel");

        horizontalLayout_5->addWidget(verifyLabel);

        verifyLineEdit = new QLineEdit(page);
        verifyLineEdit->setObjectName("verifyLineEdit");

        horizontalLayout_5->addWidget(verifyLineEdit);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        checkLabel = new QLabel(page);
        checkLabel->setObjectName("checkLabel");
        checkLabel->setMinimumSize(QSize(0, 25));
        checkLabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_6->addWidget(checkLabel);

        checkLineEdit = new QLineEdit(page);
        checkLineEdit->setObjectName("checkLineEdit");
        checkLineEdit->setMinimumSize(QSize(0, 25));
        checkLineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_6->addWidget(checkLineEdit);

        getCodeBtn = new QPushButton(page);
        getCodeBtn->setObjectName("getCodeBtn");
        getCodeBtn->setMinimumSize(QSize(0, 0));
        getCodeBtn->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_6->addWidget(getCodeBtn);


        verticalLayout_3->addLayout(horizontalLayout_6);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        confirmBtn = new QPushButton(page);
        confirmBtn->setObjectName("confirmBtn");
        confirmBtn->setMinimumSize(QSize(0, 0));
        confirmBtn->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setPointSize(9);
        confirmBtn->setFont(font);

        horizontalLayout_7->addWidget(confirmBtn);

        cancelBtn = new QPushButton(page);
        cancelBtn->setObjectName("cancelBtn");
        cancelBtn->setMinimumSize(QSize(0, 0));
        cancelBtn->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_7->addWidget(cancelBtn);


        verticalLayout_3->addLayout(horizontalLayout_7);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);

        verticalLayout->addWidget(stackedWidget);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(RegisterDialog);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RegisterDialog);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialog)
    {
        RegisterDialog->setWindowTitle(QCoreApplication::translate("RegisterDialog", "Dialog", nullptr));
        errorTipLabel->setText(QString());
        userLabel->setText(QCoreApplication::translate("RegisterDialog", "\347\224\250\346\210\267\357\274\232", nullptr));
        emailLabel->setText(QCoreApplication::translate("RegisterDialog", "\351\202\256\347\256\261\357\274\232", nullptr));
        passLabel->setText(QCoreApplication::translate("RegisterDialog", "\345\257\206\347\240\201\357\274\232", nullptr));
        verifyLabel->setText(QCoreApplication::translate("RegisterDialog", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", nullptr));
        checkLabel->setText(QCoreApplication::translate("RegisterDialog", "\351\252\214\350\257\201\347\240\201\357\274\232", nullptr));
        getCodeBtn->setText(QCoreApplication::translate("RegisterDialog", "\350\216\267\345\217\226", nullptr));
        confirmBtn->setText(QCoreApplication::translate("RegisterDialog", "\347\241\256\350\256\244", nullptr));
        cancelBtn->setText(QCoreApplication::translate("RegisterDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterDialog: public Ui_RegisterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
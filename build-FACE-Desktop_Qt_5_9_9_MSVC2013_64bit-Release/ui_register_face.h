/********************************************************************************
** Form generated from reading UI file 'register_face.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_FACE_H
#define UI_REGISTER_FACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_REGISTER_FACE
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_6;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_4;
    QLabel *labelDisplay;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QLineEdit *lineEditFaceIdR;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *lineEditLicenseR;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelMatch;
    QHBoxLayout *horizontalLayout;
    QLabel *label_6;
    QLineEdit *lineEditFaceIdM;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLineEdit *lineEditLicenseM;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_5;
    QLabel *labelMatch_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QLineEdit *lineEditFaceIdM_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_8;
    QLineEdit *lineEditLicenseM_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QToolButton *btnRegister;
    QPushButton *btnConfirmRegister;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btnMatch;
    QPushButton *btnConfirmMatch;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QMainWindow *REGISTER_FACE)
    {
        if (REGISTER_FACE->objectName().isEmpty())
            REGISTER_FACE->setObjectName(QStringLiteral("REGISTER_FACE"));
        REGISTER_FACE->resize(866, 369);
        centralwidget = new QWidget(REGISTER_FACE);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        labelDisplay = new QLabel(groupBox);
        labelDisplay->setObjectName(QStringLiteral("labelDisplay"));
        labelDisplay->setStyleSheet(QStringLiteral("background-color: rgb(85, 255, 255);"));

        verticalLayout_4->addWidget(labelDisplay);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_5->addWidget(label);

        lineEditFaceIdR = new QLineEdit(groupBox);
        lineEditFaceIdR->setObjectName(QStringLiteral("lineEditFaceIdR"));

        horizontalLayout_5->addWidget(lineEditFaceIdR);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        lineEditLicenseR = new QLineEdit(groupBox);
        lineEditLicenseR->setObjectName(QStringLiteral("lineEditLicenseR"));

        horizontalLayout_4->addWidget(lineEditLicenseR);


        verticalLayout_4->addLayout(horizontalLayout_4);

        verticalLayout_4->setStretch(0, 8);
        verticalLayout_4->setStretch(1, 1);
        verticalLayout_4->setStretch(2, 1);

        gridLayout->addLayout(verticalLayout_4, 0, 0, 1, 1);


        horizontalLayout_6->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        labelMatch = new QLabel(groupBox_2);
        labelMatch->setObjectName(QStringLiteral("labelMatch"));
        labelMatch->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 255);"));

        verticalLayout_3->addWidget(labelMatch);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout->addWidget(label_6);

        lineEditFaceIdM = new QLineEdit(groupBox_2);
        lineEditFaceIdM->setObjectName(QStringLiteral("lineEditFaceIdM"));

        horizontalLayout->addWidget(lineEditFaceIdM);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        lineEditLicenseM = new QLineEdit(groupBox_2);
        lineEditLicenseM->setObjectName(QStringLiteral("lineEditLicenseM"));

        horizontalLayout_3->addWidget(lineEditLicenseM);


        verticalLayout_3->addLayout(horizontalLayout_3);

        verticalLayout_3->setStretch(0, 8);
        verticalLayout_3->setStretch(1, 1);
        verticalLayout_3->setStretch(2, 1);

        gridLayout_2->addLayout(verticalLayout_3, 0, 0, 1, 1);


        horizontalLayout_6->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        labelMatch_2 = new QLabel(groupBox_3);
        labelMatch_2->setObjectName(QStringLiteral("labelMatch_2"));
        labelMatch_2->setStyleSheet(QStringLiteral("background-color: rgb(170, 255, 127);"));

        verticalLayout_5->addWidget(labelMatch_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_7->addWidget(label_7);

        lineEditFaceIdM_2 = new QLineEdit(groupBox_3);
        lineEditFaceIdM_2->setObjectName(QStringLiteral("lineEditFaceIdM_2"));

        horizontalLayout_7->addWidget(lineEditFaceIdM_2);


        verticalLayout_5->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_8->addWidget(label_8);

        lineEditLicenseM_2 = new QLineEdit(groupBox_3);
        lineEditLicenseM_2->setObjectName(QStringLiteral("lineEditLicenseM_2"));

        horizontalLayout_8->addWidget(lineEditLicenseM_2);


        verticalLayout_5->addLayout(horizontalLayout_8);

        verticalLayout_5->setStretch(0, 8);
        verticalLayout_5->setStretch(1, 1);
        verticalLayout_5->setStretch(2, 1);

        gridLayout_3->addLayout(verticalLayout_5, 0, 0, 1, 1);


        horizontalLayout_6->addWidget(groupBox_3);


        verticalLayout_6->addLayout(horizontalLayout_6);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        btnRegister = new QToolButton(centralwidget);
        btnRegister->setObjectName(QStringLiteral("btnRegister"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnRegister->sizePolicy().hasHeightForWidth());
        btnRegister->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(btnRegister);

        btnConfirmRegister = new QPushButton(centralwidget);
        btnConfirmRegister->setObjectName(QStringLiteral("btnConfirmRegister"));

        verticalLayout->addWidget(btnConfirmRegister);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        btnMatch = new QPushButton(centralwidget);
        btnMatch->setObjectName(QStringLiteral("btnMatch"));
        sizePolicy.setHeightForWidth(btnMatch->sizePolicy().hasHeightForWidth());
        btnMatch->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(btnMatch);

        btnConfirmMatch = new QPushButton(centralwidget);
        btnConfirmMatch->setObjectName(QStringLiteral("btnConfirmMatch"));
        sizePolicy.setHeightForWidth(btnConfirmMatch->sizePolicy().hasHeightForWidth());
        btnConfirmMatch->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(btnConfirmMatch);


        horizontalLayout_2->addLayout(verticalLayout_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_6->addLayout(horizontalLayout_2);

        verticalLayout_6->setStretch(0, 12);
        verticalLayout_6->setStretch(1, 1);

        gridLayout_4->addLayout(verticalLayout_6, 0, 0, 1, 1);

        REGISTER_FACE->setCentralWidget(centralwidget);

        retranslateUi(REGISTER_FACE);

        QMetaObject::connectSlotsByName(REGISTER_FACE);
    } // setupUi

    void retranslateUi(QMainWindow *REGISTER_FACE)
    {
        REGISTER_FACE->setWindowTitle(QApplication::translate("REGISTER_FACE", "MainWindow", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("REGISTER_FACE", "\346\263\250\345\206\214\345\214\272", Q_NULLPTR));
        labelDisplay->setText(QString());
        label->setText(QApplication::translate("REGISTER_FACE", "faceID:", Q_NULLPTR));
        label_2->setText(QApplication::translate("REGISTER_FACE", "username:", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("REGISTER_FACE", "\346\225\260\346\215\256\345\272\223\345\214\271\351\205\215\345\214\272", Q_NULLPTR));
        labelMatch->setText(QString());
        label_6->setText(QApplication::translate("REGISTER_FACE", "faceID:", Q_NULLPTR));
        label_5->setText(QApplication::translate("REGISTER_FACE", "username:", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("REGISTER_FACE", "\346\234\254\345\234\260\345\233\276\347\211\207\345\214\271\351\205\215\345\214\272", Q_NULLPTR));
        labelMatch_2->setText(QString());
        label_7->setText(QApplication::translate("REGISTER_FACE", "faceID:", Q_NULLPTR));
        label_8->setText(QApplication::translate("REGISTER_FACE", "username:", Q_NULLPTR));
        btnRegister->setText(QApplication::translate("REGISTER_FACE", "\346\263\250\345\206\214", Q_NULLPTR));
        btnConfirmRegister->setText(QApplication::translate("REGISTER_FACE", "\347\241\256\350\256\244\346\263\250\345\206\214", Q_NULLPTR));
        btnMatch->setText(QApplication::translate("REGISTER_FACE", "database\345\214\271\351\205\215", Q_NULLPTR));
        btnConfirmMatch->setText(QApplication::translate("REGISTER_FACE", "local\345\214\271\351\205\215", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class REGISTER_FACE: public Ui_REGISTER_FACE {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_FACE_H

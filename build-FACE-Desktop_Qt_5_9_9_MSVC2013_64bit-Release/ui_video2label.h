/********************************************************************************
** Form generated from reading UI file 'video2label.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEO2LABEL_H
#define UI_VIDEO2LABEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VIDEO2LABEL
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *labelDisplay;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnShot;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnStart;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnStop;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QMainWindow *VIDEO2LABEL)
    {
        if (VIDEO2LABEL->objectName().isEmpty())
            VIDEO2LABEL->setObjectName(QStringLiteral("VIDEO2LABEL"));
        VIDEO2LABEL->resize(562, 444);
        centralwidget = new QWidget(VIDEO2LABEL);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        labelDisplay = new QLabel(centralwidget);
        labelDisplay->setObjectName(QStringLiteral("labelDisplay"));
        labelDisplay->setStyleSheet(QStringLiteral("background-color: rgb(17, 52, 52);"));

        verticalLayout->addWidget(labelDisplay);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnShot = new QPushButton(centralwidget);
        btnShot->setObjectName(QStringLiteral("btnShot"));

        horizontalLayout->addWidget(btnShot);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btnStart = new QPushButton(centralwidget);
        btnStart->setObjectName(QStringLiteral("btnStart"));

        horizontalLayout->addWidget(btnStart);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        btnStop = new QPushButton(centralwidget);
        btnStop->setObjectName(QStringLiteral("btnStop"));

        horizontalLayout->addWidget(btnStop);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 9);
        verticalLayout->setStretch(1, 1);

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        VIDEO2LABEL->setCentralWidget(centralwidget);

        retranslateUi(VIDEO2LABEL);

        QMetaObject::connectSlotsByName(VIDEO2LABEL);
    } // setupUi

    void retranslateUi(QMainWindow *VIDEO2LABEL)
    {
        VIDEO2LABEL->setWindowTitle(QApplication::translate("VIDEO2LABEL", "MainWindow", Q_NULLPTR));
        labelDisplay->setText(QApplication::translate("VIDEO2LABEL", "TextLabel", Q_NULLPTR));
        btnShot->setText(QApplication::translate("VIDEO2LABEL", "screenshot", Q_NULLPTR));
        btnStart->setText(QApplication::translate("VIDEO2LABEL", "start", Q_NULLPTR));
        btnStop->setText(QApplication::translate("VIDEO2LABEL", "stop", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class VIDEO2LABEL: public Ui_VIDEO2LABEL {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEO2LABEL_H

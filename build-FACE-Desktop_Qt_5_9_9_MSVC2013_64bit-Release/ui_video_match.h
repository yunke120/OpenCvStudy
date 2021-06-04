/********************************************************************************
** Form generated from reading UI file 'video_match.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEO_MATCH_H
#define UI_VIDEO_MATCH_H

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

class Ui_VIDEO_MATCH
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *labelDisplay;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QLabel *labelMatch;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnPlay;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnMatch;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnStop;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QMainWindow *VIDEO_MATCH)
    {
        if (VIDEO_MATCH->objectName().isEmpty())
            VIDEO_MATCH->setObjectName(QStringLiteral("VIDEO_MATCH"));
        VIDEO_MATCH->resize(895, 520);
        centralwidget = new QWidget(VIDEO_MATCH);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        labelDisplay = new QLabel(centralwidget);
        labelDisplay->setObjectName(QStringLiteral("labelDisplay"));
        labelDisplay->setStyleSheet(QStringLiteral("background-color: rgb(0, 85, 0);"));

        verticalLayout->addWidget(labelDisplay);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 9);

        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        labelMatch = new QLabel(centralwidget);
        labelMatch->setObjectName(QStringLiteral("labelMatch"));
        labelMatch->setStyleSheet(QStringLiteral("background-color: rgb(255, 170, 255);"));

        verticalLayout_2->addWidget(labelMatch);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 9);

        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnPlay = new QPushButton(centralwidget);
        btnPlay->setObjectName(QStringLiteral("btnPlay"));

        horizontalLayout_2->addWidget(btnPlay);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btnMatch = new QPushButton(centralwidget);
        btnMatch->setObjectName(QStringLiteral("btnMatch"));

        horizontalLayout_2->addWidget(btnMatch);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        btnStop = new QPushButton(centralwidget);
        btnStop->setObjectName(QStringLiteral("btnStop"));

        horizontalLayout_2->addWidget(btnStop);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalLayout_3->setStretch(0, 9);
        verticalLayout_3->setStretch(1, 1);

        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);

        VIDEO_MATCH->setCentralWidget(centralwidget);

        retranslateUi(VIDEO_MATCH);

        QMetaObject::connectSlotsByName(VIDEO_MATCH);
    } // setupUi

    void retranslateUi(QMainWindow *VIDEO_MATCH)
    {
        VIDEO_MATCH->setWindowTitle(QApplication::translate("VIDEO_MATCH", "MainWindow", Q_NULLPTR));
        label_2->setText(QApplication::translate("VIDEO_MATCH", "\350\247\206\351\242\221\346\230\276\347\244\272\345\214\272\357\274\232", Q_NULLPTR));
        labelDisplay->setText(QString());
        label_3->setText(QApplication::translate("VIDEO_MATCH", "\345\214\271\351\205\215\345\233\276\347\211\207\345\214\272", Q_NULLPTR));
        labelMatch->setText(QString());
        btnPlay->setText(QApplication::translate("VIDEO_MATCH", "play", Q_NULLPTR));
        btnMatch->setText(QApplication::translate("VIDEO_MATCH", "match", Q_NULLPTR));
        btnStop->setText(QApplication::translate("VIDEO_MATCH", "stop", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class VIDEO_MATCH: public Ui_VIDEO_MATCH {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEO_MATCH_H

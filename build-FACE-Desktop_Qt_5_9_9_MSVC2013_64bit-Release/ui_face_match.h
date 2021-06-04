/********************************************************************************
** Form generated from reading UI file 'face_match.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACE_MATCH_H
#define UI_FACE_MATCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FACE_MATCH
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QLabel *label_Origin;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QLabel *labelMatch;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnLoad;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnMatch;
    QSpacerItem *horizontalSpacer_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FACE_MATCH)
    {
        if (FACE_MATCH->objectName().isEmpty())
            FACE_MATCH->setObjectName(QStringLiteral("FACE_MATCH"));
        FACE_MATCH->resize(883, 493);
        centralwidget = new QWidget(FACE_MATCH);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        label_Origin = new QLabel(centralwidget);
        label_Origin->setObjectName(QStringLiteral("label_Origin"));
        label_Origin->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 127);"));

        verticalLayout->addWidget(label_Origin);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 9);

        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_2->addWidget(label_4);

        labelMatch = new QLabel(centralwidget);
        labelMatch->setObjectName(QStringLiteral("labelMatch"));
        labelMatch->setStyleSheet(QStringLiteral("background-color: rgb(85, 255, 127);"));

        verticalLayout_2->addWidget(labelMatch);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 9);

        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnLoad = new QPushButton(centralwidget);
        btnLoad->setObjectName(QStringLiteral("btnLoad"));

        horizontalLayout_2->addWidget(btnLoad);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btnMatch = new QPushButton(centralwidget);
        btnMatch->setObjectName(QStringLiteral("btnMatch"));

        horizontalLayout_2->addWidget(btnMatch);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);

        FACE_MATCH->setCentralWidget(centralwidget);
        menubar = new QMenuBar(FACE_MATCH);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 883, 22));
        FACE_MATCH->setMenuBar(menubar);
        statusbar = new QStatusBar(FACE_MATCH);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        FACE_MATCH->setStatusBar(statusbar);

        retranslateUi(FACE_MATCH);

        QMetaObject::connectSlotsByName(FACE_MATCH);
    } // setupUi

    void retranslateUi(QMainWindow *FACE_MATCH)
    {
        FACE_MATCH->setWindowTitle(QApplication::translate("FACE_MATCH", "MainWindow", Q_NULLPTR));
        label_3->setText(QApplication::translate("FACE_MATCH", "\345\216\237\345\233\276", Q_NULLPTR));
        label_Origin->setText(QString());
        label_4->setText(QApplication::translate("FACE_MATCH", "\345\214\271\351\205\215\344\272\272\350\204\270\345\233\276", Q_NULLPTR));
        labelMatch->setText(QString());
        btnLoad->setText(QApplication::translate("FACE_MATCH", "\350\275\275\345\205\245\345\233\276\345\203\217", Q_NULLPTR));
        btnMatch->setText(QApplication::translate("FACE_MATCH", "\345\274\200\345\247\213\345\214\271\351\205\215", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FACE_MATCH: public Ui_FACE_MATCH {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACE_MATCH_H

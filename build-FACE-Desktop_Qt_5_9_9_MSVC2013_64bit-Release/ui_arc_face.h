/********************************************************************************
** Form generated from reading UI file 'arc_face.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARC_FACE_H
#define UI_ARC_FACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ARC_FACE
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ARC_FACE)
    {
        if (ARC_FACE->objectName().isEmpty())
            ARC_FACE->setObjectName(QStringLiteral("ARC_FACE"));
        ARC_FACE->resize(534, 430);
        centralwidget = new QWidget(ARC_FACE);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        ARC_FACE->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ARC_FACE);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 534, 22));
        ARC_FACE->setMenuBar(menubar);
        statusbar = new QStatusBar(ARC_FACE);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ARC_FACE->setStatusBar(statusbar);

        retranslateUi(ARC_FACE);

        QMetaObject::connectSlotsByName(ARC_FACE);
    } // setupUi

    void retranslateUi(QMainWindow *ARC_FACE)
    {
        ARC_FACE->setWindowTitle(QApplication::translate("ARC_FACE", "MainWindow", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ARC_FACE: public Ui_ARC_FACE {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARC_FACE_H

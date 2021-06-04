/********************************************************************************
** Form generated from reading UI file 'opencv_video.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENCV_VIDEO_H
#define UI_OPENCV_VIDEO_H

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

class Ui_OPENCV_VIDEO
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *OPENCV_VIDEO)
    {
        if (OPENCV_VIDEO->objectName().isEmpty())
            OPENCV_VIDEO->setObjectName(QStringLiteral("OPENCV_VIDEO"));
        OPENCV_VIDEO->resize(800, 600);
        menubar = new QMenuBar(OPENCV_VIDEO);
        menubar->setObjectName(QStringLiteral("menubar"));
        OPENCV_VIDEO->setMenuBar(menubar);
        centralwidget = new QWidget(OPENCV_VIDEO);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        OPENCV_VIDEO->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(OPENCV_VIDEO);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        OPENCV_VIDEO->setStatusBar(statusbar);

        retranslateUi(OPENCV_VIDEO);

        QMetaObject::connectSlotsByName(OPENCV_VIDEO);
    } // setupUi

    void retranslateUi(QMainWindow *OPENCV_VIDEO)
    {
        OPENCV_VIDEO->setWindowTitle(QApplication::translate("OPENCV_VIDEO", "MainWindow", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OPENCV_VIDEO: public Ui_OPENCV_VIDEO {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENCV_VIDEO_H

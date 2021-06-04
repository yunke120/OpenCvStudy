#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "submain.h"

#include <opencv2/core/types_c.h>
#include <opencv/inc/opencv2/core/core.hpp>
#include <opencv/inc/opencv2/highgui/highgui.hpp>
#include <opencv/inc/opencv2/imgproc/imgproc.hpp>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cv::Mat ret_image;
    /* 0灰度图  -1原图 1RGB*/
//    cv::Mat img = cv::imread("B:\\QT_Project\\Face\\internetimg\\2.jpg", 1);
    cv::Mat img = cv::imread("../internetimg/3.jpg", 1);

//    cv::cvtColor(img, ret_image, CV_BGR2RGB);


    cv::namedWindow("display image",CV_WINDOW_NORMAL);
    cv::imshow("display image", img);
    cv::imwrite("../rimg/3.png", img);
    cv::waitKey(0);
    cv::destroyWindow("display image");
    exit(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


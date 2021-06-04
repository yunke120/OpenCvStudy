#include "opencv_video.h"
#include "ui_opencv_video.h"
#include "submain.h"


using namespace cv;

OPENCV_VIDEO::OPENCV_VIDEO(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OPENCV_VIDEO)
{
    ui->setupUi(this);

#if 0 /* 只能显示一祯图片 */
    cv::VideoCapture camera(0);
    cv::Mat image;
    bool isok = camera.read(image);
    if(!isok) camera.release();

    cv::imshow("video test", image);
    cv::waitKey(30);
    camera.release();
#endif

    /* 修改为不断获取摄像头数据并显示 */

    cv::VideoCapture camera(0); /* 创建一个视频对象 */
//    cv::VideoCapture camera("B:\\QT_Project\\Face\\video\\4K超清金色粒子动态背景视频素材.mp4");
    cv::Mat image;
    cv::Mat grayimage;
    cv::Mat saveimage;
//    cv::CascadeClassifier cascadeClassifier("B:\\QT_Project\\Face\\exe\\haarcascade_frontalface_alt2.xml");
    cv::VideoWriter video_writer("B:\\QT_Project\\Face\\wvideo\\video_4.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25.0, Size(640, 480));


    if(!camera.isOpened()) exit(0);
    bool ret = false;
    while (true) {
        ret = camera.read(image);
        if(!ret) {
            qDebug() << "Can't receive frame (stream end?). Exiting ...";
            break;
        }

//        cv::cvtColor(image, grayimage, cv::COLOR_BGR2GRAY);
//        cv::flip(grayimage, saveimage, -1); /* 0:180, -1 */
        video_writer.write(image); /* 保存实时视频 */
//        cv::imshow("video test", saveimage); /* 灰度显示 */
//        cv::imshow("video test", grayimage); /* 灰度显示 */
        cv::imshow("video test", image); /* 原图显示 */


        if(27 == cv::waitKey(1)) break; /* 按下ESC键退出 */
    }

    qDebug() << "exit0";

    camera.release();
    video_writer.release();
    cv::destroyAllWindows();
    exit(0);

}

OPENCV_VIDEO::~OPENCV_VIDEO()
{
    delete ui;
}

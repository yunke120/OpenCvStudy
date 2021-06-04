#include "video2label.h"
#include "ui_video2label.h"


VIDEO2LABEL::VIDEO2LABEL(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VIDEO2LABEL)
{
    ui->setupUi(this);

    video_timer = new QTimer(this);

    connect(video_timer, &QTimer::timeout, this, [=]() {
        if(!camera.isOpened()) {
            qDebug() << "camera opened failed.";
            return ;
        }
        if(!camera.read(image)) {
            qDebug() << "The read image is empty";
            return ;
        }

        cv::cvtColor(image, grayimage, CV_BGR2GRAY);
        cv::cvtColor(image, ret_image, CV_BGR2RGB);
        if(SAVE_IMAGE_FLAGE)
        {
            SAVE_IMAGE_FLAGE = false;
            qsrand(QDateTime::currentDateTime().toTime_t());
            QString origin_image = QString("B:\\QT_Project\\Face\\rimg\\%1.png").arg(qrand());
            cv::imwrite(origin_image.toStdString(), ret_image);
//            IplImage imgTmp(ret_image);
//            IplImage *img1 = cvCloneImage(&imgTmp); /* 深拷贝 */
//            cvSave(origin_image.toLatin1().data(),&imgTmp);
        }

//        QImage q_image((const uchar*)grayimage.data,grayimage.cols,grayimage.rows, QImage::Format_Grayscale8);
//        QImage q_image((const uchar*)image.data,image.cols,image.rows, QImage::Format_RGB888); /* 截图彩色 */
        QImage q_image((const uchar*)ret_image.data,ret_image.cols,ret_image.rows, QImage::Format_RGB888);

        ui->labelDisplay->setPixmap(QPixmap::fromImage(q_image));


    });
}

VIDEO2LABEL::~VIDEO2LABEL()
{
    delete ui;
}

void VIDEO2LABEL::CutIplImage(IplImage *src, IplImage *dst, int x, int y)
{
    CvSize size = cvSize(dst->width, dst->height);//区域大小
    cvSetImageROI(src, cvRect(x, y, size.width, size.height));//设置源图像ROI
    cvCopy(src, dst); //复制图像
    cvResetImageROI(src);//源图像用完后，清空ROI
}

void VIDEO2LABEL::on_btnShot_clicked()
{
    SAVE_IMAGE_FLAGE = true;
}

void VIDEO2LABEL::on_btnStart_clicked()
{
    camera.open(0);
    camera.set(CV_CAP_PROP_FRAME_WIDTH,ui->labelDisplay->width());
    camera.set(CV_CAP_PROP_FRAME_HEIGHT,ui->labelDisplay->height());
    if(!camera.isOpened()) {
        qDebug() << "camera0 open failed.";
        return;
    }

    video_timer->start(25);
}

void VIDEO2LABEL::on_btnStop_clicked()
{
    video_timer->stop();

    camera.release();
    image.release();
}

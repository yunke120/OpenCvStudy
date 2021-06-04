#ifndef VIDEO2LABEL_H
#define VIDEO2LABEL_H

#include <QMainWindow>
#include "submain.h"
using namespace cv;
namespace Ui {
class VIDEO2LABEL;
}

class VIDEO2LABEL : public QMainWindow
{
    Q_OBJECT

public:
    explicit VIDEO2LABEL(QWidget *parent = nullptr);
    ~VIDEO2LABEL();

    void CutIplImage(IplImage* src, IplImage* dst, int x, int y);

private slots:
    void on_btnShot_clicked();

    void on_btnStart_clicked();

    void on_btnStop_clicked();

private:
    Ui::VIDEO2LABEL *ui;
    bool SAVE_IMAGE_FLAGE = false;
    QTimer *video_timer;
    cv::VideoCapture camera; /* 创建一个视频对象 */
    cv::Mat image;
    cv::Mat ret_image;
    cv::Mat grayimage;

};

#endif // VIDEO2LABEL_H

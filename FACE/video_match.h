#ifndef VIDEO_MATCH_H
#define VIDEO_MATCH_H

#include <QMainWindow>
#include "submain.h"
namespace Ui {
class VIDEO_MATCH;
}

class VIDEO_MATCH : public QMainWindow
{
    Q_OBJECT

public:
    explicit VIDEO_MATCH(QWidget *parent = nullptr);
    ~VIDEO_MATCH();

    //裁剪图片
    void CutIplImage(IplImage* src, IplImage* dst, int x, int y);

    QStringList getImageFilePath(QString dirpath = "../rimg");

    void getImagesFeature(QString dirpath,QList<ASF_FaceFeature>& list);
    void getMatchImageFeature(cv::Mat img, ASF_FaceFeature& feature1);

private slots:

    void displayVideo();

    void on_btnPlay_clicked();

    void on_btnMatch_clicked();

    void on_btnStop_clicked();

private:
    Ui::VIDEO_MATCH *ui;
    bool SAVE_IMAGE_FLAGE = false;
    QTimer *video_timer;

    cv::VideoCapture camera; /* 创建一个视频对象 */
    cv::Mat image;
    cv::Mat ret_image;
    cv::Mat grayimage;

    CvHaarClassifierCascade *cascadeClassifier;

    QString origin_img_filepath;
    QStringList files_path;
    MHandle handle = NULL; /* 引擎句柄 */
    ASF_FaceFeature feature1; /* 源图特征 */
    QList<ASF_FaceFeature> feature_list; /* 声明特征集合 */

    double similarity;
};

#endif // VIDEO_MATCH_H

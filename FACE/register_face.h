#ifndef REGISTER_FACE_H
#define REGISTER_FACE_H

#include <QMainWindow>
#include "submain.h"
#include "face_bin.h"
#include "face_sql.h"

namespace Ui {
class REGISTER_FACE;
}

class REGISTER_FACE : public QMainWindow
{
    Q_OBJECT

public:
    explicit REGISTER_FACE(QWidget *parent = nullptr);
    ~REGISTER_FACE();

    void init_system();
    void CutIplImage(IplImage* src, IplImage* dst, int x, int y);
//    void getImageFeature(IplImage* img);
    bool getFeatureByImage(QString img_path, ASF_FaceFeature& feature);
    bool getFeatureByVideo(cv::Mat image, ASF_FaceFeature& feature);
//    bool registerFaceFeature(QString filepath, ASF_FaceFeature feature); /* 注册人脸数据 */
//    bool registerFaceFeature(QString filepath, face_data_def face_data);

//    bool readFaceFeature(QString filepath, QList<ASF_FaceFeature>& list);
//    bool readFaceFeature(QString filepath, QList<face_data_def>& face_data);

    QStringList getImageFilePath(QString dirpath = "../rimg");

    void getImagesFeature(QString dirpath,QList<ASF_FaceFeature>& list);




private slots:
    void on_btnRegister_clicked();

    void on_btnConfirmRegister_clicked();

    void on_btnMatch_clicked();

    void on_btnConfirmMatch_clicked();

    void displayVideo();

    void btnActionImage();
    void btnActionVideo();

//    void on_pushButton_clicked();

//    void on_pushButton_2_clicked();

private:
    Ui::REGISTER_FACE *ui;
    FACE_BIN *face_bin;
    FACE_SQL *face_sql;
    QSqlDatabase db;

    MHandle image_handle = NULL; /* 引擎句柄 */
    QList<ASF_FaceFeature> feature_list; /* 声明特征集合 */
//    QList<face_data_def> face_data_list;
    ASF_FaceFeature reg_feature;
    ASF_FaceFeature img_feature;
    QString img_path;
    QStringList img_file_list;

    QTimer *video_timer;

    cv::VideoCapture camera; /* 创建一个视频对象 */


    CvHaarClassifierCascade *cascadeClassifier;
    CvMemStorage *memStorage;
    double similarity;

    bool REGISTER_FLAG = false;
    bool SAVE_IMAGE_DATA_FLAG = false;

    bool Action_Image_Clicked_Flag = false;
    bool Action_Video_Clicked_Flag = false;


};

#endif // REGISTER_FACE_H

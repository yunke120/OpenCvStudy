#ifndef FACE_MATCH_H
#define FACE_MATCH_H

#include <QMainWindow>
#include "submain.h"
namespace Ui {
class FACE_MATCH;
}

class FACE_MATCH : public QMainWindow
{
    Q_OBJECT

public:
    explicit FACE_MATCH(QWidget *parent = nullptr);
    ~FACE_MATCH();



    //裁剪图片
    void CutIplImage(IplImage* src, IplImage* dst, int x, int y);
    //时间戳转换为日期格式
    void timestampToTime(char* timeStamp, char* dateTime, int dateTimeSize);

    QStringList getImageFilePath(QString dirpath = "../rimg");

    void getImagesFeature(QString dirpath,QList<ASF_FaceFeature>& list);

    bool writeFaceFeature(QList<ASF_FaceFeature> *list);

    bool readFaceFeature(QString filepath, QList<ASF_FaceFeature>& list);

private slots:
    void on_btnLoad_clicked();

    void on_btnMatch_clicked();

private:
    Ui::FACE_MATCH *ui;
    QString origin_img_filepath;
    QStringList files_path;
    MHandle handle = NULL; /* 引擎句柄 */
    ASF_FaceFeature copyfeature; /* 源图特征 */
    QList<ASF_FaceFeature> feature_list; /* 声明特征集合 */

    double similarity;
#define IMAGE_PRETREATMENT /* 第二种方式，先把所有的图片特征保存在缓存中，再进行匹配 */
#define IMAGE_DIRECTLY /* 直接比较 */


};

#endif // FACE_MATCH_H

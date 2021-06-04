#ifndef ARC_FACE_H
#define ARC_FACE_H

#include <QMainWindow>

#include "submain.h"

namespace Ui {
class ARC_FACE;
}

class ARC_FACE : public QMainWindow
{
    Q_OBJECT

public:
    explicit ARC_FACE(QWidget *parent = nullptr);
    ~ARC_FACE();

    //裁剪图片
    void CutIplImage(IplImage* src, IplImage* dst, int x, int y);
    //时间戳转换为日期格式
    void timestampToTime(char* timeStamp, char* dateTime, int dateTimeSize);

private:
    Ui::ARC_FACE *ui;
};

#endif // ARC_FACE_H

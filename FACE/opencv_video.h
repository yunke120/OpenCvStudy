#ifndef OPENCV_VIDEO_H
#define OPENCV_VIDEO_H

#include <QMainWindow>


namespace Ui {
class OPENCV_VIDEO;
}

class OPENCV_VIDEO : public QMainWindow
{
    Q_OBJECT

public:
    explicit OPENCV_VIDEO(QWidget *parent = nullptr);
    ~OPENCV_VIDEO();

private:
    Ui::OPENCV_VIDEO *ui;
};

#endif // OPENCV_VIDEO_H

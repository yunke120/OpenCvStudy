#ifndef TEST_UI_H
#define TEST_UI_H

#include <QWidget>
#include "face_bin.h"

namespace Ui {
class TEST_UI;
}

class TEST_UI : public QWidget
{
    Q_OBJECT

public:
    explicit TEST_UI(QWidget *parent = nullptr);
    ~TEST_UI();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::TEST_UI *ui;
    FACE_BIN *m_face_bin;
};

#endif // TEST_UI_H

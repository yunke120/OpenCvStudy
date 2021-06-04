#include "test_ui.h"
#include "ui_test_ui.h"

TEST_UI::TEST_UI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TEST_UI)
{
    ui->setupUi(this);
//    m_face_bin = new FACE_BIN("ss");
}

TEST_UI::~TEST_UI()
{
    delete ui;
}

void TEST_UI::on_pushButton_clicked()
{
//    m_face_bin->create_file();
}

void TEST_UI::on_pushButton_2_clicked()
{

}

void TEST_UI::on_pushButton_3_clicked()
{

}

#include "face_bin.h"
#include <QApplication>
//FACE_BIN::FACE_BIN(QObject *parent) : QObject(parent)
//{

//}

FACE_BIN::FACE_BIN(QObject *parent, QString file_name) : QObject(parent)
{
    QString str1 = qApp->applicationDirPath();
    QString str = str1 + "/" +file_name+".hs";
    path = str;
    QFile file(str);
    if(!file.exists()) {
        file.open(QIODevice::WriteOnly);
        file.close();
    }

}

QString FACE_BIN::get_file_name()
{
    return path;
}

//bool FACE_BIN::create(const QString file_path, QString &file_name)
//{
//    file_name = QFileDialog::getSaveFileName(nullptr, "this", file_path, "*.hs");
//    QFile file(file_name);
//    if(!file.open(QIODevice::WriteOnly)) return false;
//    file.close();
//    return true;
//}

bool FACE_BIN::write(const QString file_name, const FACE_DATA_TypeDef face_data)
{;
    QFile file(file_name);
    if(!file.open(QIODevice::WriteOnly)) return false;

    QDataStream stream(&file);

    stream << face_data.t_id;
    stream << face_data.t_username;
    stream << face_data.t_feature.featureSize;
    qDebug() << face_data.t_feature.featureSize;
//    stream.writeRawData(reinterpret_cast<char*>(face_data.t_id), sizeof (face_data.t_id));
//    stream.writeRawData(reinterpret_cast<char*>(face_data.t_feature.featureSize), sizeof (face_data.t_feature.featureSize));
    stream.writeRawData(reinterpret_cast<char*>(face_data.t_feature.feature), face_data.t_feature.featureSize);

    stream << face_data.t_image.type();
    stream << face_data.t_image.cols;
    stream << face_data.t_image.rows;
    const size_t image_data_size = face_data.t_image.cols *
                                   face_data.t_image.rows *
                                   face_data.t_image.elemSize();

    QByteArray data = QByteArray::fromRawData((const char*)face_data.t_image.ptr(), int(image_data_size));
    stream << data;

    file.close();
    return true;
}

bool FACE_BIN::append(const QString file_name, const FACE_DATA_TypeDef face_data)
{
    QFile file(file_name);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append)) return false;

    QDataStream stream(&file);

    stream << face_data.t_id;
    stream << face_data.t_username;
    stream << face_data.t_feature.featureSize;
//    stream.writeRawData(reinterpret_cast<char*>(face_data.t_id), sizeof (face_data.t_id));
//    stream.writeRawData(reinterpret_cast<char*>(face_data.t_feature.featureSize), sizeof (face_data.t_feature.featureSize));
    stream.writeRawData(reinterpret_cast<char*>(face_data.t_feature.feature), face_data.t_feature.featureSize);

    stream << face_data.t_image.type();
    stream << face_data.t_image.cols;
    stream << face_data.t_image.rows;
    const size_t image_data_size = face_data.t_image.cols *
                                   face_data.t_image.rows *
                                   face_data.t_image.elemSize();

    QByteArray data = QByteArray::fromRawData((const char*)face_data.t_image.ptr(), int(image_data_size));
    stream << data;

    file.close();
    return true;
}

int FACE_BIN::readAll(const QString file_name, QList<FACE_DATA_TypeDef> &face_data_list)
{
    int i = 0;
    QFile file(file_name);
    if(!file.open(QIODevice::ReadOnly)) return 0;

    QDataStream stream(&file);

    FACE_DATA_TypeDef fd;

    while (!file.atEnd()) {
        stream >> fd.t_id >> fd.t_username;
        stream >> fd.t_feature.featureSize;
        fd.t_feature.feature = reinterpret_cast<MByte*>(malloc(fd.t_feature.featureSize));
        stream.readRawData(reinterpret_cast<char*>(fd.t_feature.feature), fd.t_feature.featureSize);

        int type, cols, rows;
        stream >> type >> cols >> rows;
        QByteArray data;
        stream >> data;

        cv::Mat img = cv::Mat(rows, cols, type, (void*)data.data());

        fd.t_image = img;

        face_data_list << fd;
        fd = {0};
        free(fd.t_feature.feature);
        i++;
    }

    file.close();

    return i;



}

bool FACE_BIN::read(const QString file_name, FACE_DATA_TypeDef& face_data, int index)
{
    int i = 0;
    QFile file(file_name);
    if(!file.open(QIODevice::ReadOnly)) return false;

    QDataStream stream(&file);
    FACE_DATA_TypeDef fd;
    while (!file.atEnd()) {
        stream >> fd.t_id >> fd.t_username;
        stream >> fd.t_feature.featureSize;
        fd.t_feature.feature = reinterpret_cast<MByte*>(malloc(fd.t_feature.featureSize));
        stream.readRawData(reinterpret_cast<char*>(fd.t_feature.feature), fd.t_feature.featureSize);

        int type, cols, rows;
        stream >> type >> cols >> rows;
        QByteArray data;
        stream >> data;

        cv::Mat img = cv::Mat(rows, cols, type, (void*)data.data());

        fd.t_image = img;

        i++;
        if(i == index) {
            face_data = fd;
            fd = {0};
            free(fd.t_feature.feature);
            file.close();
            return true;
        }

        fd = {0};
        free(fd.t_feature.feature);
    }
    file.close();
    return false;
}




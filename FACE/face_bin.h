#ifndef FACE_BIN_H
#define FACE_BIN_H

#include <QObject>
#include "submain.h"

class FACE_BIN : public QObject
{
    Q_OBJECT
public:
//    FACE_BIN(QObject *parent = nullptr);

    FACE_BIN(QObject *parent = nullptr, QString file_name = "face_bin");
    QString get_file_name();
//    bool create(const QString file_path, QString& file_name);
    bool write(const QString file_name, const FACE_DATA_TypeDef face_data);
    bool append(const QString file_name, const FACE_DATA_TypeDef face_data);

//    bool safeWrite();
//    bool safeRead();

    int readAll(const QString file_name, QList<FACE_DATA_TypeDef>& face_data_list);
    bool read(const QString file_name, FACE_DATA_TypeDef& face_data, int index);


private:
    QString path;

signals:

};

#endif // FACE_BIN_H

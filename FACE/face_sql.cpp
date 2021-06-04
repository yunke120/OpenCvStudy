#include "face_sql.h"

FACE_SQL::FACE_SQL(QObject *parent) : QObject(parent)
{
}

QSqlDatabase FACE_SQL::create_db(QString fileName, QString identifier)
{
    QSqlDatabase db;
    QString name = QCoreApplication::applicationDirPath() + "/" + fileName + ".db";
//    QFile file(name);
//    if(!file.exists()) {
        db = QSqlDatabase::addDatabase("QSQLITE", identifier);
        db.setDatabaseName(name);
//}
    return db;
}

bool FACE_SQL::open_db(QSqlDatabase db)
{
    return db.open();
}

bool FACE_SQL::isExistTable(QSqlDatabase db, QString table)
{
    if (!open_db(db)) {
        return false;
    }
    QSqlQuery query(db);
    query.exec(QString("select count(*) from sqlite_master where type='table' and name='%1'").arg(table));    //关键的判断
    if (query.next())
    {
        if (query.value(0).toInt() == 0)
        {
            return false; /* not exist */
        }
    }
    return true;
}

/* pl9  user16-8*/
bool FACE_SQL::create_table(QSqlDatabase db, QString table)
{
    /*
       create table userData
       (
         id int unsigned not null primary key,
         username char(16) not null,
         pl char(9) not null,
         reserve1 char(9),
         reserve2 char(9),
         featuresize int unsigned not null,
         imgtype int not null,
         imgcols int unsigned not null,
         imgrows int unsigned not null,
         imgsize int unsigned not null
       );

                  featuredata blob not null,
         imgdata blob not null,
//         stime datetime not null
    */

    if(!open_db(db)){
        qDebug() << "open failed";
        return false;
    }
    QSqlQuery sqlquery(db);
    return sqlquery.exec(table);
}

bool FACE_SQL::insert_data_into_table(QSqlDatabase db, QString table, SQL_DATA_TypeDef *data_t)
{
    QSqlQuery sqlquery(db);
    /* 此处判断唯一性 */
    QString command = QString("INSERT INTO %1 (id,username,pl,reserve1,reserve2,featuresize,featuredata,imgtype,imgcols,imgrows,imgsize,imgdata) VALUES (:id,:username,:pl,:reserve1,:reserve2,:featuresize,:featuredata,:imgtype,:imgcols,:imgrows,:imgsize,:imgdata);").arg(table);
    qDebug() << command;
    sqlquery.prepare(command);
    qDebug() << 1;
    sqlquery.bindValue(":id", data_t->t_id);
    sqlquery.bindValue(":username", data_t->t_username);
    sqlquery.bindValue(":pl", data_t->t_pl);
    sqlquery.bindValue(":reserve1", data_t->t_reserve1);
    sqlquery.bindValue(":reserve2", data_t->t_reserve2);
    sqlquery.bindValue(":featuresize", data_t->t_featuresize);
//    QByteArray featureByte = QByteArray::fromRawData((const char*)data_t->t_featuredata, data_t->t_featuresize);
    sqlquery.bindValue(":featuredata", data_t->t_featuredata);
    sqlquery.bindValue(":imgtype", data_t->t_imgtype);
    sqlquery.bindValue(":imgcols", data_t->t_imgcols);
    sqlquery.bindValue(":imgrows", data_t->t_imgrows);
    sqlquery.bindValue(":imgsize", data_t->t_imgsize);
//    const size_t data_size = data_t->t_imgcols * data_t->t_imgrows * data_t->t_imgsize;
//    QByteArray imgByte = QByteArray::fromRawData((const char*)data_t->t_imgdata, int(data_size));
    sqlquery.bindValue(":imgdata", data_t->t_imgdata);
//    sqlquery.bindValue(":stime", data_t->t_datetime);
    if(sqlquery.exec()) return true;
    else {
        qDebug() << sqlquery.lastError().text();
        return false;
    }

}

bool FACE_SQL::output_table(QSqlDatabase db, QString table, SQL_DATA_TypeDef &data_t)
{
    return true;
}

bool FACE_SQL::get_userInfo(QSqlDatabase db, QString table, int id, SQL_DATA_TypeDef &data_t)
{
    QSqlQuery sqlquery(db);
    QString command = QString("select * from %1 where id = %2;").arg(table).arg(id);
    if(!sqlquery.exec(command)) {
        qDebug() << sqlquery.lastError().text();
        return false;
    }
    else {
        sqlquery.next();
        data_t.t_id = sqlquery.value(0).toInt();
        data_t.t_username = sqlquery.value(1).toString();
        data_t.t_pl = sqlquery.value(2).toString();
        data_t.t_reserve1 = sqlquery.value(3).toString();
        data_t.t_reserve2 = sqlquery.value(4).toString();
        data_t.t_featuresize = sqlquery.value(5).toInt();
        data_t.t_featuredata = sqlquery.value(6).toByteArray();

//        data_t.t_featuredata = (unsigned char*)data1.data();
        data_t.t_imgtype = sqlquery.value(7).toInt();
        data_t.t_imgcols = sqlquery.value(8).toInt();
        data_t.t_imgrows = sqlquery.value(9).toInt();
        data_t.t_imgsize = sqlquery.value(10).toInt();

        QByteArray data2 = sqlquery.value(11).toByteArray();
        data_t.t_imgdata = data2;
//        data_t.t_datetime = sqlquery.value(12).toDateTime();

        return true;
    }
}

bool FACE_SQL::update_userInfo(QSqlDatabase db, QString table, int id, QString col_name, QString new_value)
{
    QSqlQuery sqlquery(db);
    QString command = QString("update %1 set %2 = %3 where id = :id;").arg(table)
                                                                    .arg(col_name)
                                                                    .arg(new_value);
    sqlquery.bindValue(":id", id);
    if(!sqlquery.exec()) {
        return false;
    }
    else {
        return true;
    }

}

/*  select id from userData; */



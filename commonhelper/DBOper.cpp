#include "DBOper.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

DBOper *DBOper::m_dbOper = nullptr;

DBOper::DBOper(QObject *parent) : QObject(parent){
    m_DB = QSqlDatabase::addDatabase("QSQLITE");
    m_DB.setDatabaseName("manage.db");
    m_DB.open();

    if(! m_DB.isOpen()){
        qDebug() << "数据库打开失败";
    }
}

DBOper *DBOper::getInstance(){
    if(!DBOper::m_dbOper){
        DBOper::m_dbOper = new DBOper();
    }
    return DBOper::m_dbOper;
}

QList<QVariantMap> DBOper::query(QString sql, QVariantList params){
    QList<QVariantMap> result ;
    if(m_DB.isOpen()){
        QSqlQuery squery(m_DB);
        squery.prepare(sql);
        for(int i = 0 ;i < params.size();i++){
            QVariant & p = params[i];
            squery.bindValue(i,p);
        }

        squery.exec();
        while(squery.next()){
            QSqlRecord record = squery.record();
            int fieldCount = record.count();
            QVariantMap rowMap ;
            for(int i = 0 ; i < fieldCount ; i++){
                QString fieldName = record.fieldName(i);
                QVariant fieldValue = record.value(i);
                rowMap.insert(fieldName,fieldValue);
            }
            result.append(rowMap);
        }
        QSqlError error = squery.lastError();
        if(error.type() != QSqlError::NoError){
            qDebug() << error.text();
        }
    }
    return result;
}

QVariant DBOper::querySingleResult(QString sql, QVariantList params){
    QList<QVariantMap> result = this->query(sql, params);

    if(!result.isEmpty()){
        if(!result[0].isEmpty()){
            return result[0].first();
        }
    }
    return QVariant();
}

void DBOper::exec(QString sql, QVariantList params, int *lastInseredId){
    if(m_DB.isOpen()){
        QSqlQuery squery(m_DB);
        squery.prepare(sql);
        for(int i = 0 ;i < params.size();i++){
            QVariant & p = params[i];
            squery.bindValue(i,p);
        }
        if(squery.exec()){
            if(lastInseredId){
                *lastInseredId = squery.lastInsertId().toInt();
            }
            //return true;
        }
        else{
            QSqlError error = squery.lastError();
            qDebug() << error.text();
        }
    }
}



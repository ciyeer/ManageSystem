#ifndef CONNECTION_H
#define CONNECTION_H
#include <QtSql>
#include <QDebug>
#include "qdom.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QMessageBox>

static bool creatConnection(){
    QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("manage.db");    //数据库的名字
    if (!m_db.open()){
        qDebug() << "Error: connection with database failed";
        return false;
    }
    else{
        qDebug() << "Database: connection correct";
    }

    QSqlQuery query(m_db);
    //商家表
    query.exec(QString("create table t_user(user_id int primary key, user_account varchar, user_password varchar, user_role int)"));
    query.exec(QString("create table t_user(id varchar primary key, name varchar)"));
    query.exec(QString("insert into t_user values(1, 'admin', '123456', 0)"));
    query.exec(QString("insert into t_user values(2, 'user', '12345', 1)"));


    //    QSqlQuery query;
    //商家表
    //    query.exec(QString("create table t_user(user_id int primary key, user_account varchar, user_password varchar, user_role int)"));
    //    query.exec(QString("create table t_user(id varchar primary key, name varchar)"));
    //    query.exec(QString("insert into t_user values(1, 'admin', '123456', 0)"));
    //    query.exec(QString("insert into t_user values(2, 'user', '12345', 1)"));

    //品牌表
    //    query.exec("create table brand(id varchar primary key, name varchar, factory varchar, price int, sum int, sell int, last int)");
    //    query.exec(QString("insert into brand values('1', '奥迪A6', '一汽大众', 36, 50, 10, 40)"));
    //    query.exec(QString("insert into brand values('2', '捷达', '一汽大众', 34, 20, 5, 15)"));
    //    query.exec(QString("insert into brand values('3', '宝来', '一汽大众', 41, 80, 20, 60)"));
    //    query.exec(QString("insert into brand values('4', '奔驰', '一汽大众', 83, 40, 15, 25)"));
    //    query.exec(QString("insert into brand values('5', '毕加索', '二汽神龙', 39, 50, 15, 35)"));
    //    query.exec(QString("insert into brand values('6', '富康', '二汽神龙', 28, 60, 10, 50)"));
    //    query.exec(QString("insert into brand values('7', '标致307', '二汽神龙', 27, 70, 20, 50)"));
    //    query.exec(QString("insert into brand values('8', '桑塔纳', '上海大众', 25, 75, 25, 50)"));
    //    query.exec(QString("insert into brand values('9', '帕萨特', '上海大众', 27, 65, 20, 45)"));
    //    //密码表
    //    query.exec("create table passwordtable(username varchar primary key, password varchar)");
    //    query.exec("insert into passwordtable values('Administrator', '123456')");
    return true;
}

static bool createXml(){
    QFile file("data.xml");
    if(file.exists()){
        return true;
    }
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        return false;
    }
    QDomDocument doc;
    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);     //自动格式化
    writer.writeStartDocument();        //开始文档  自动声明xml版本等
    writer.writeEndDocument();          //结束文档
    QDomElement root = doc.createElement(QString("日常销售清单"));    //根元素
    doc.appendChild(root);              //设置根元素
    QTextStream out(&file);
    doc.save(out, 4);                   //保存doc到out也就是到file
    file.close();
    return true;
}

#endif

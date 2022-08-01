#ifndef CONNECTION_H
#define CONNECTION_H
#include <QtSql>
#include <QDebug>
#include "qdom.h"
#include <QFile>
#include <QXmlStreamWriter>

static bool creatConnection(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("hostname");
    db.setDatabaseName("data.db");    //数据库的名字，此库位于build-Manager-Desktop_Qt_5_8_0_MinGW_32bit-Debug路径中
    db.setUserName("zhanag");
    db.setPassword("123456");
    if(!db.open()){
        return false;
    }
    QSqlQuery query;
    //商家表
    query.exec(QString("create table factory(id varchar primary key, name varchar)"));
    query.exec(QString("insert into factory values('0', '请选择厂家')"));
    query.exec(QString("insert into factory values('1', '一汽大众')"));
    query.exec(QString("insert into factory values('2', '二汽神龙')"));
    query.exec(QString("insert into factory values('3', '上海大众')"));
    //品牌表
    query.exec("create table brand(id varchar primary key, name varchar, factory varchar, price int, sum int, sell int, last int)");
    query.exec(QString("insert into brand values('1', '奥迪A6', '一汽大众', 36, 50, 10, 40)"));
    query.exec(QString("insert into brand values('2', '捷达', '一汽大众', 34, 20, 5, 15)"));
    query.exec(QString("insert into brand values('3', '宝来', '一汽大众', 41, 80, 20, 60)"));
    query.exec(QString("insert into brand values('4', '奔驰', '一汽大众', 83, 40, 15, 25)"));
    query.exec(QString("insert into brand values('5', '毕加索', '二汽神龙', 39, 50, 15, 35)"));
    query.exec(QString("insert into brand values('6', '富康', '二汽神龙', 28, 60, 10, 50)"));
    query.exec(QString("insert into brand values('7', '标致307', '二汽神龙', 27, 70, 20, 50)"));
    query.exec(QString("insert into brand values('8', '桑塔纳', '上海大众', 25, 75, 25, 50)"));
    query.exec(QString("insert into brand values('9', '帕萨特', '上海大众', 27, 65, 20, 45)"));
    //密码表
    query.exec("create table passwordtable(username varchar primary key, password varchar)");
    query.exec("insert into passwordtable values('Administrator', '123456')");
    return true;
}

static bool createXml(){    // 此函数较原书有修改
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

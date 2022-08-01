#ifndef COMMONHELPER_H
#define COMMONHELPER_H

#include <QWidget>
#include <QFile>
#include <QDebug>
#include <QApplication>

class CommonHelper{
public:
    static void setStyle(const QString strPath){
        QFile file(strPath);
        if(!file.open(QFile::ReadOnly)){
            qDebug() << "load css file failed!";
            return;
        }
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
        file.close();
    }
};

#endif // COMMONHELPER_H

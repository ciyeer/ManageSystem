#include "mainwidget.h"
#include <QApplication>
#include "commonhelper/connection.h"

int main(int argc, char *argv[]){
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    if(!creatConnection()){
         return 1;
     }  
    QApplication a(argc, argv);
    MainWidget w;
    w.show();

    return a.exec();
}

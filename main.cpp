#include "mainwidget.h"
#include <QApplication>
#include "commonhelper/connection.h"

int main(int argc, char *argv[]){
    if(!creatConnection()){
         return 1;
     }
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    MainWidget w;
    w.show();

    return a.exec();
}

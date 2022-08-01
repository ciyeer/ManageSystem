#include "mainwidget.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]){
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    MainWidget w;
    w.show();

    return a.exec();
}
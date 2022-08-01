#include "queryinfodialog.h"
#include "ui_queryinfodialog.h"

QueryInfoDialog::QueryInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueryInfoDialog){
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
}

QueryInfoDialog::~QueryInfoDialog(){
    delete ui;
}

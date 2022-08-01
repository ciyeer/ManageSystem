#include "queryuserinfodialog.h"
#include "ui_queryuserinfodialog.h"

QueryUserInfoDialog::QueryUserInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueryUserInfoDialog){
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
}

QueryUserInfoDialog::~QueryUserInfoDialog(){
    delete ui;
}

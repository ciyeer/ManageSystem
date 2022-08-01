#include "deleteuserinfodialog.h"
#include "ui_deleteuserinfodialog.h"

deleteUserInfoDialog::deleteUserInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteUserInfoDialog){
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
}

deleteUserInfoDialog::~deleteUserInfoDialog(){
    delete ui;
}

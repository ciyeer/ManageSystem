#include "modifyuserinfodialog.h"
#include "ui_modifyuserinfodialog.h"

ModifyUserInfoDialog::ModifyUserInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyUserInfoDialog){
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
}

ModifyUserInfoDialog::~ModifyUserInfoDialog(){
    delete ui;
}

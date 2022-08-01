#include "clearuserinfodialog.h"
#include "ui_clearuserinfodialog.h"

ClearUserInfoDialog::ClearUserInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClearUserInfoDialog){
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
}

ClearUserInfoDialog::~ClearUserInfoDialog(){
    delete ui;
}

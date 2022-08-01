#include "modifyinfodialog.h"
#include "ui_modifyinfodialog.h"

ModifyInfoDialog::ModifyInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyInfoDialog){
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
}

ModifyInfoDialog::~ModifyInfoDialog(){
    delete ui;
}

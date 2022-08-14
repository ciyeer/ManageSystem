#include "userwidget.h"
#include "ui_userwidget.h"

UserWidget::UserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserWidget){
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);

    connect(ui->exitBtn, &QPushButton::clicked,
            this, &UserWidget::slotReturnLoginWidget);
    connect(ui->modifyInfo, &QPushButton::clicked,
            this, &UserWidget::slotModifyUserInfo);
    connect(ui->serachuser, &QPushButton::clicked,
            this, &UserWidget::slotQueryUserInfo);
}

void UserWidget::slotReturnLoginWidget(){
    emit display(0);
}

void UserWidget::slotModifyUserInfo(){

}

void UserWidget::slotQueryUserInfo(){

}

UserWidget::~UserWidget(){
    delete ui;
}

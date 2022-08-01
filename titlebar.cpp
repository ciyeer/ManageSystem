#include "titlebar.h"
#include "ui_titlebar.h"

TitleBar::TitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleBar){
    ui->setupUi(this);

    ui->titleLabel->setText("员工管理系统");
    connect(ui->closeBtn, &QPushButton::clicked,
            this, &TitleBar::slotCloseWidget);
    connect(ui->minBtn, &QPushButton::clicked,
            this, &TitleBar::slotMiniSizedWidget);
}

void TitleBar::slotCloseWidget(){
    parentWidget()->close();
}

void TitleBar::slotMiniSizedWidget(){
    parentWidget()->showMinimized();
}

TitleBar::~TitleBar(){
    delete ui;
}

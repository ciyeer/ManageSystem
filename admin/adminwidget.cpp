#include "adminwidget.h"
#include "ui_adminwidget.h"

AdminWidget::AdminWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWidget){
    ui->setupUi(this);

    //connection();
    m_pModel = new QSqlTableModel(this);
    m_pModel->setTable("t_user");
    ui->user_tableView->setModel(m_pModel);
    m_pModel->select();
    //ui->user_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void AdminWidget::connection(){
    connect(ui->adduserbtn, &QPushButton::clicked,
            this, &AdminWidget::slotAddUser);
    connect(ui->deleteuserbtn, &QPushButton::clicked,
            this, &AdminWidget::slotDeleteUser);
    connect(ui->modifyBtn, &QPushButton::clicked,
            this, &AdminWidget::slotModifyUserInfo);
    connect(ui->serachuser, &QPushButton::clicked,
            this, &AdminWidget::slotQueryUser);
    connect(ui->clearBtn, &QPushButton::clicked,
            this, &AdminWidget::slotClearUserInfo);
    connect(ui->exitBtn, &QPushButton::clicked,
            this, &AdminWidget::slotReturnLoginWidget);
}

void AdminWidget::slotAddUser(){
    AddUserInfoDialog addDlg;
    addDlg.exec();
}

void AdminWidget::slotQueryUser(){
    QueryUserInfoDialog queryDlg;
    queryDlg.exec();
}

void AdminWidget::slotDeleteUser(){
    deleteUserInfoDialog deleteDlg;
    deleteDlg.exec();
}

void AdminWidget::slotModifyUserInfo(){
    ModifyUserInfoDialog modifyDlg;
    modifyDlg.exec();
}

void AdminWidget::slotClearUserInfo(){
    ClearUserInfoDialog clearDlg;
    clearDlg.exec();
}

void AdminWidget::slotReturnLoginWidget(){
    emit display(0);
}

AdminWidget::~AdminWidget(){
    delete ui;
}




#include "adduserinfodialog.h"
#include "ui_adduserinfodialog.h"
#include <QDebug>
#include <QMessageBox>

AddUserInfoDialog::AddUserInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserInfoDialog){
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    connect(ui->varietyBtn, &QPushButton::clicked,
            this, &AddUserInfoDialog::slotVariety);
    connect(ui->cancelBtn, &QPushButton::clicked,
            this, &AddUserInfoDialog::slotCancel);

    QSqlDatabase m_db;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("manage.db");

    if (!m_db.open()){
        qDebug() << "Error: connection with database failed";
    }
    else{
        qDebug() << "Database: connection correct";
    }
}

void AddUserInfoDialog::slotVariety(){
    QString strId = ui->id_edit->text();
    QString strName = ui->name_edit->text();
    QString strSex = ui->sex_edit->text();
    QString strAge = ui->age_edit->text();
    QString strPost = ui->post_edit->text();
    QString strTel = ui->phone_edit->text();
    QString strPasswd = ui->passwd_edit->text();
    QString strRole = ui->role_edit->text();

    QString id = "17";
    int role = 1;

    QSqlQuery query(m_db);
    query.exec("select *from t_user");
    query.prepare("INSERT INTO t_user (user_id,user_account,user_password,user_role)"
                  "VALUES (:id, :name, :password, :role)");
    query.bindValue(":name", strName);
    query.bindValue(":password", strPasswd);
    query.bindValue(":phoneNo", strTel);
    query.bindValue(":role", role);
    query.bindValue(":id", strId);
    query.bindValue(":sex", strSex);
    query.bindValue(":age", strAge);
    query.bindValue(":post", strPost);

    if(query.exec()){
        QMessageBox::information(this,"温馨提示","添加成功");
    }
    else{
        QMessageBox::information(this,"温馨提示","添加失败");
    }
    this->close();
}

void AddUserInfoDialog::slotCancel(){

}

AddUserInfoDialog::~AddUserInfoDialog(){
    delete ui;
}


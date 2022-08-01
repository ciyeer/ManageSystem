
#include "adminaddaccountwidget.h"
#include "ui_adminaddaccountwidget.h"
#include <QDebug>
#include "cmessagebox/cmessagebox.h"
#include <QMessageBox>

AdminAddAccountWidget::AdminAddAccountWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminAddAccountWidget){
    ui->setupUi(this);
}

AdminAddAccountWidget::~AdminAddAccountWidget(){
    delete ui;
}

void AdminAddAccountWidget::on_varietyBtn_clicked(){
    QString name = ui->username_lineedit->text();
    QString passwd = ui->passwd_lineedit->text();
    QString phoneNo = ui->phoneNo_lineedit->text();
    QString id = "17";
    QString role = "subadmin";

    QSqlQuery query(m_db);
    query.exec("select *from t_user");
    query.prepare("INSERT INTO t_user (user_id,user_account,user_password,user_role)"
                  "VALUES (:id, :name, :password, :role)");
    query.bindValue(":name", name);
    query.bindValue(":password", passwd);
    query.bindValue(":phoneNo", phoneNo);
    query.bindValue(":role", role);

    if(query.exec()){
        QMessageBox::information(this,"温馨提示","添加成功");
    }
    else
        QMessageBox::information(this,"温馨提示","添加失败");

    this->close();
}



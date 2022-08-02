#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QMessageBox>
#include "cmessagebox/cmessagebox.h"
#include <QDebug>

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget){
    ui->setupUi(this);

    connect(ui->OkBtn, &QPushButton::clicked,
            this, &LoginWidget::slotsOnLoginBtn);
    connect(ui->CancelBtn, &QPushButton::clicked,
            this, &LoginWidget::slotsOnCancelBtn);
}

void LoginWidget::setUserInfo(const UserInfo &userInfo){
    if(userInfo.user_role == admin)
        emit display(1);
    if(userInfo.user_role == subadmin)
        emit display(2);
}

void LoginWidget::slotsOnLoginBtn(){
    QString username = ui->lineEdit_username->text();

    QString password = ui->lineEdit_password->text();
    qDebug() << username << password;

    int roles[] = {admin, subadmin};

    int role = roles[ui->comboBox_type->currentIndex()];

    if(username.isEmpty()){
        CMessageBox::showCMessageBox(this, "警告", "请输入用户名", MESSAGE_WARNNING, BUTTON_OK, true);
        return;
    }

    if(password.isEmpty()){
        QMessageBox::warning(this, "警告", "请输入密码", "确定");
        return;
    }

    m_pUserService = new UserService;

    if(m_pUserService->login(username, password, role)){

        CMessageBox::showCMessageBox(this, "提示", "登录成功", MESSAGE_INFORMATION, BUTTON_OK, true);

        UserInfo info = m_pUserService->userInfo(username);

        setUserInfo(info);

        this->close();
    }
    else{
        QMessageBox::information(this,"提示","登录失败,请确认用户名密码是否正确","确定");
    }
}

void LoginWidget::slotsOnCancelBtn(){
    this->parentWidget()->close();
}

LoginWidget::~LoginWidget(){
    delete ui;
    delete m_pUserService;
    m_pUserService = nullptr;
}


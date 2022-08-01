#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "service/userservice.h"

namespace Ui {
class LoginWidget;
}

enum Permission{
    admin,
    subadmin
};

class LoginWidget : public QWidget{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();
    void setUserInfo(const UserInfo &userInfo);

signals:
    void display(int);  // 这里的参数表示要显示的界面层级

public slots:
    void slotsOnLoginBtn();
    void slotsOnCancelBtn();

private:
    Ui::LoginWidget *ui;
    UserService *m_pUserService;
};

#endif // LOGINWIDGET_H

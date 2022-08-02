#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QStackedLayout>
#include <QStackedWidget>
#include "admin/adminwidget.h"
#include "user/userwidget.h"
#include "loginwidget.h"
#include "titlebar.h"
#include "statusbar.h"
#include "mouseevent.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public MouseEvent{
    Q_OBJECT

public:
    explicit MainWidget(MouseEvent *parent = nullptr);
    ~MainWidget();

    void setUsetInfo(const UserInfo &userInfo);
    void setStyle(const QString &);

private:
    AdminWidget *m_pAdminWidget;
    UserWidget  *m_pUserWidget;
    LoginWidget *m_pLoginWidget;
    TitleBar    *m_pTitleBar;
    StatusBar   *m_pStatusBar;
    QStackedLayout *m_pStackedLayout;
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H

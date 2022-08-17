#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QStackedLayout>
#include <QMouseEvent>
#include <QPoint>
#include "admin/adminwidget.h"
#include "user/userwidget.h"
#include "loginwidget.h"
#include "titlebar.h"
#include "statusbar.h"
// #include "mouseevent.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    void setUsetInfo(const UserInfo &userInfo);
    void setStyle(const QString &);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool m_bisPressed;
    QPoint m_point;     // 鼠标点击的坐标

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

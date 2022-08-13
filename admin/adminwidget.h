#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QWidget>
#include <QSqlTableModel>
#include "admin/adminaddaccountwidget.h"
#include "adduserinfodialog.h"
#include "queryuserinfodialog.h"
#include "modifyuserinfodialog.h"
#include "deleteuserinfodialog.h"
#include "clearuserinfodialog.h"

namespace Ui {
class AdminWidget;
}

class AdminWidget : public QWidget{
    Q_OBJECT

public:
    explicit AdminWidget(QWidget *parent = nullptr);
    ~AdminWidget();

    void setUpTableView();

    void connection();

signals:
    void display(int);

public slots:
    // 添加用户
    void slotAddUser();
    // 查询用户
    void slotQueryUser();
    // 删除用户
    void slotDeleteUser();
    // 修改用户信息
    void slotModifyUserInfo();
    // 清空用户信息
    void slotClearUserInfo();
    // 刷新(更新)信息
    void slotFlushUserInfo();
    // 返回登录界面
    void slotReturnLoginWidget();
    // QTableView点击列头的排序操作(初始化时，开启了列头clicked和关联信号槽)
    void sortByColumn(int col);

private:
    Ui::AdminWidget *ui;

    AdminAddAccountWidget *m_pAdminAddAccountWidget;

    QSqlTableModel *m_pModel;
};

#endif // ADMINWIDGET_H

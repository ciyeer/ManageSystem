#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QWidget>
#include <QSqlTableModel>
#include <QMenu>
#include <QAction>
#include "admin/adminaddaccountwidget.h"
#include "adduserinfodialog.h"

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

    void setTableViewContextMenu();

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
    void slotSaveUserInfo();
    // 刷新(更新)信息
    void slotFlushUserInfo();
    // 返回登录界面
    void slotReturnLoginWidget();
    // QTableView点击列头的排序操作(初始化时，开启了列头clicked和关联信号槽)
    void sortByColumn(int col);
    // 删除一行
    void slotDeleteContextMenu(const QPoint pos);

private:
    Ui::AdminWidget *ui;

    AdminAddAccountWidget *m_pAdminAddAccountWidget;

    QSqlTableModel *m_pModel;

    QMenu *tableviewMenu;

    QAction *deleteAction;

    bool m_bModifyFlag;
};

#endif // ADMINWIDGET_H

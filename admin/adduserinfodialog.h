#ifndef ADDUSERINFODIALOG_H
#define ADDUSERINFODIALOG_H

#include <QDialog>
#include "service/userservice.h"
#include "service/accountinfo.h"

namespace Ui {
class AddUserInfoDialog;
}

class AddUserInfoDialog : public QDialog{
    Q_OBJECT

public:
    explicit AddUserInfoDialog(QWidget *parent = nullptr);
    ~AddUserInfoDialog();

public slots:
    void slotVariety();      // 确认按钮
    void slotCancel();       // 取消按钮

private:
    Ui::AddUserInfoDialog *ui;
    QSqlDatabase m_db;
};

#endif // ADDUSERINFODIALOG_H

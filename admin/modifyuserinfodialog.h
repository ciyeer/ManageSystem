#ifndef MODIFYUSERINFODIALOG_H
#define MODIFYUSERINFODIALOG_H

#include <QDialog>

namespace Ui {
class ModifyUserInfoDialog;
}

class ModifyUserInfoDialog : public QDialog{
    Q_OBJECT

public:
    explicit ModifyUserInfoDialog(QWidget *parent = nullptr);
    ~ModifyUserInfoDialog();

private:
    Ui::ModifyUserInfoDialog *ui;
};

#endif // MODIFYUSERINFODIALOG_H

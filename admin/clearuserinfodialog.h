#ifndef CLEARUSERINFODIALOG_H
#define CLEARUSERINFODIALOG_H

#include <QDialog>

namespace Ui {
class ClearUserInfoDialog;
}

class ClearUserInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClearUserInfoDialog(QWidget *parent = nullptr);
    ~ClearUserInfoDialog();

private:
    Ui::ClearUserInfoDialog *ui;
};

#endif // CLEARUSERINFODIALOG_H

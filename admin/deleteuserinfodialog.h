#ifndef DELETEUSERINFODIALOG_H
#define DELETEUSERINFODIALOG_H

#include <QDialog>

namespace Ui {
class deleteUserInfoDialog;
}

class deleteUserInfoDialog : public QDialog{
    Q_OBJECT

public:
    explicit deleteUserInfoDialog(QWidget *parent = nullptr);
    ~deleteUserInfoDialog();

private:
    Ui::deleteUserInfoDialog *ui;
};

#endif // DELETEUSERINFODIALOG_H

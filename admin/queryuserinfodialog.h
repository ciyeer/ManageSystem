#ifndef QUERYUSERINFODIALOG_H
#define QUERYUSERINFODIALOG_H

#include <QDialog>

namespace Ui {
class QueryUserInfoDialog;
}

class QueryUserInfoDialog : public QDialog{
    Q_OBJECT

public:
    explicit QueryUserInfoDialog(QWidget *parent = nullptr);
    ~QueryUserInfoDialog();

private:
    Ui::QueryUserInfoDialog *ui;
};

#endif // QUERYUSERINFODIALOG_H

#ifndef QUERYINFODIALOG_H
#define QUERYINFODIALOG_H

#include <QDialog>

namespace Ui {
class QueryInfoDialog;
}

class QueryInfoDialog : public QDialog{
    Q_OBJECT

public:
    explicit QueryInfoDialog(QWidget *parent = nullptr);
    ~QueryInfoDialog();

private:
    Ui::QueryInfoDialog *ui;
};

#endif // QUERYINFODIALOG_H

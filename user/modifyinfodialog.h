#ifndef MODIFYINFODIALOG_H
#define MODIFYINFODIALOG_H

#include <QDialog>

namespace Ui {
class ModifyInfoDialog;
}

class ModifyInfoDialog : public QDialog{
    Q_OBJECT

public:
    explicit ModifyInfoDialog(QWidget *parent = nullptr);
    ~ModifyInfoDialog();

private:
    Ui::ModifyInfoDialog *ui;
};

#endif // MODIFYINFODIALOG_H

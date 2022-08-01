#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QWidget>
#include "modifyinfodialog.h"
#include "queryinfodialog.h"

namespace Ui {
class UserWidget;
}

class UserWidget : public QWidget{
    Q_OBJECT

signals:
    void display(int);

public:
    explicit UserWidget(QWidget *parent = nullptr);
    ~UserWidget();

public slots:
    void slotReturnLoginWidget();
    void slotModifyUserInfo();
    void slotQueryUserInfo();

private:
    Ui::UserWidget *ui;
};

#endif // USERWIDGET_H

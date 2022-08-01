#ifndef ADMINADDACCOUNTWIDGET_H
#define ADMINADDACCOUNTWIDGET_H

#include <QWidget>
#include "service/userservice.h"
#include "service/accountinfo.h"

namespace Ui {
class AdminAddAccountWidget;
}

class AdminAddAccountWidget : public QWidget{
    Q_OBJECT

public:
    explicit AdminAddAccountWidget(QWidget *parent = nullptr);
    ~AdminAddAccountWidget();

private slots:

    void on_varietyBtn_clicked();

private:
    Ui::AdminAddAccountWidget *ui;
    UserService *m_pUserService;
    QSqlDatabase m_db;
};

#endif // ADMINADDACCOUNTWIDGET_H

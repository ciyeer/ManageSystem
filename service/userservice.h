#ifndef USERSERVICE_H
#define USERSERVICE_H

#include <QObject>
#include "commonhelper/DBOper.h"
#include "service/accountinfo.h"

class UserService : public QObject{
    Q_OBJECT
public:

    bool login(QString username, QString password, int role);

    UserInfo userInfo(QString username);
};

#endif // USERSERVICE_H

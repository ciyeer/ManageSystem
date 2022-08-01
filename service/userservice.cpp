#include "userservice.h"
#include <QDebug>

UserService::UserService(){}

bool UserService::login(QString username, QString password, int role){

    QString sql = "select * from t_user where user_account = ? and user_password = ? and user_role = ?";

    QList<QVariantMap> result = DBOper::getInstance()->query(sql, QVariantList() << username << password << role);

    return !result.empty();
}

UserInfo UserService::userInfo(QString username){

    QString sql = "select * from t_user where user_account = ?";

    QList<QVariantMap> result = DBOper::getInstance()->query(sql, QVariantList() << username);

    UserInfo info;

    if(!result.isEmpty()){

        QVariantMap & map = result[0];

        info.user_account = map["user_account"].toString();

        info.user_id = map["user_id"].toInt();

        info.user_role = map["user_role"].toInt();
    }

    return info;
}


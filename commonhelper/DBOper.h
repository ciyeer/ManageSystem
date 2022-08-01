#ifndef DBOPER_H
#define DBOPER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariantMap>
#include <QList>

class DBOper : public QObject{
    Q_OBJECT
private:
    explicit DBOper(QObject *parent = nullptr);

public:

    static DBOper *getInstance();

    QList<QVariantMap> query(QString sql, QVariantList params = QVariantList());

    QVariant querySingleResult(QString sql, QVariantList params = QVariantList());

    void exec(QString sql,QVariantList params = QVariantList(),int * lastInseredId = nullptr);

private:

    static DBOper * m_dbOper;

    QSqlDatabase m_DB;
};

#endif // DBOPER_H

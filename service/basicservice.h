#ifndef BASICSERVICE_H
#define BASICSERVICE_H

#include <QObject>
#include "accountinfo.h"
#include "commonhelper/DBOper.h"

class BasicService : public QObject{
    Q_OBJECT
public:
    explicit BasicService(QObject *parent = 0);

    QList<DepartmentInfo> departmentList();

    void delDep(int dep_id);

    void addDep(QString name);

    void updateDep(int dep_id,QString dep_name);

    int getTecIdByUserId(int user_id);

    QList<MajorInfo> majorList(int major_id);

    void addMajor(int dep_id,QString major_name);

    void updateMajor(int major_id,QString major_name);

    void delMajor(int major_id);

    QList<ClassInfo> classList(int major_id, QString class_grade);

    QList<ClassInfo> classList(int major_id, QStringList class_grades);

    void addClass(int class_major,QString class_grade,QString class_name);

    void deleteClass(int class_id);

    void updateClass(int class_id,QString class_name);

    void updateClassTec(int class_id,int tec_id);
};

#endif // BASICSERVICE_H

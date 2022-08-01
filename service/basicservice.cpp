#include "basicservice.h"

BasicService::BasicService(QObject *parent) : QObject(parent){
}

QList<DepartmentInfo> BasicService::departmentList(){
    QString sql = "select * from t_department";
    QList<QVariantMap> result = DBOper::getInstance()->query(sql);
    QList<DepartmentInfo> deps ;

    for(QVariantMap map : result){
        int dep_id = map["dep_id"].toInt();
        QString dep_name = map["dep_name"].toString();
        DepartmentInfo depInfo;
        depInfo.dep_id = dep_id;
        depInfo.dep_name = dep_name;

        deps << depInfo;
    }

    return deps;
}

void BasicService::delDep(int dep_id){
    QString sql = "delete from t_department where dep_id = ?";
    DBOper::getInstance()->exec(sql, QVariantList() << dep_id);
}

void BasicService::addDep(QString name){
    QString sql = "insert into t_department(dep_name) values(?)";
    DBOper::getInstance()->exec(sql, QVariantList() << name);
}

void BasicService::updateDep(int dep_id, QString dep_name){
    QString sql = "update t_department set dep_name = ?  where dep_id = ?";
    DBOper::getInstance()->exec(sql, QVariantList() << dep_name << dep_id);
}

int BasicService::getTecIdByUserId(int user_id){
    QString sql = "select tec_id from t_teacher where tec_user = ?";
    return DBOper::getInstance()->querySingleResult(sql, QVariantList() << user_id).toInt();
}

QList<MajorInfo> BasicService::majorList(int dep_id){
    QString sql = "select * from t_major where major_dep = ?" ;
    QList<QVariantMap> result = DBOper::getInstance()->query(sql, QVariantList() << dep_id);
    QList<MajorInfo> majors ;

    for(QVariantMap map : result){
        int major_id = map["major_id"].toInt();
        QString major_name = map["major_name"].toString();
        MajorInfo majorInfo;
        majorInfo.major_id = major_id;
        majorInfo.major_name = major_name;
        majors << majorInfo;
    }

    return majors;
}

void BasicService::addMajor(int dep_id, QString major_name){
    QString sql = "insert into t_major (major_name,major_dep) values(?,?)";
    DBOper::getInstance()->exec(sql,QVariantList()<<major_name<<dep_id);
}

void BasicService::updateMajor(int major_id, QString major_name){
    QString sql = "update t_major set major_name = ? where major_id = ?";
    DBOper::getInstance()->exec(sql,QVariantList()<<major_name<<major_id);
}

void BasicService::delMajor(int major_id){
    QString sql = "delete from t_major where major_id = ?";
    DBOper::getInstance()->exec(sql,QVariantList()<<major_id);
}

QList<ClassInfo> BasicService::classList(int major_id, QString class_grade){
    QString sql = "select * from t_class left join t_teacher on class_tec = tec_id where class_major = ? and class_grade = ?" ;
    QList<QVariantMap> result = DBOper::getInstance()->query(sql,QVariantList()<<major_id<<class_grade);
    QList<ClassInfo> classInfos ;
    for(QVariantMap map : result){
        int class_id = map["class_id"].toInt();
        QString class_name = map["class_name"].toString();
        QString tec_name = map["tec_name"].toString();

        ClassInfo classInfo;
        classInfo.class_id = class_id;
        classInfo.class_name = class_name;
        classInfo.class_grade = class_grade;
        classInfo.class_teacher = tec_name;

        classInfos<<classInfo;
    }

    return classInfos;
}

QList<ClassInfo> BasicService::classList(int major_id, QStringList class_grades){
     QList<ClassInfo> result ;

     for(QString grade : class_grades){
         result<<this->classList(major_id,grade);
     }
     return result;
}

void BasicService::addClass(int class_major, QString class_grade, QString class_name){
    QString sql = "insert into t_class (class_name,class_major,class_grade) values(?,?,?)";
    DBOper::getInstance()->exec(sql,QVariantList()<<class_name<<class_major<<class_grade);
}

void BasicService::deleteClass(int class_id){
    QString sql = "delete from t_class where class_id = ?";
    DBOper::getInstance()->exec(sql,QVariantList()<<class_id);
}

void BasicService::updateClass(int class_id, QString class_name){
    QString sql = "update t_class set class_name = ? where class_id = ?";
    DBOper::getInstance()->exec(sql,QVariantList()<<class_name<<class_id);
}

void BasicService::updateClassTec(int class_id, int tec_id){
    QString sql = "update t_class set class_tec = ? where class_id = ?";
    DBOper::getInstance()->exec(sql,QVariantList()<<tec_id<<class_id);
}

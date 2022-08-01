#ifndef ACCOUNTINFO_H
#define ACCOUNTINFO_H

#include <QString>
#include <QDate>

typedef struct UserInfo{

    int user_id;

    QString user_account;

    QString user_role;

}UserInfo;

//typedef struct UserInfo{
//    int user_id;            // id
//    QString user_account;   // 姓名/账户
//    QString user_sex;       // 性别
//    int user_age;           // 年龄
//    QString user_post;      // 职位
//    QString user_phoneno;   // 联系方式
//    //QDateTime user_hiredate;    // 电话
//    QString user_passwd;    // 账户密码
//    int user_role;          // 角色/权限
//    // ID,姓名,性别,年龄,职务,联系方式,入职时间,账户密码,权限
//}UserInfo;

typedef struct DepartmentInfo{

    int dep_id;

    QString dep_name;

}DepartmentInfo;

typedef struct MajorInfo{

    int major_id;

    QString major_name;

}MajorInfo;

typedef struct StudentInfo{

    int student_id;

    QString student_name;

    QDate stu_birthday;

    QString stu_idcard;

    QString stu_sex;

}StudentInfo;

typedef struct TeacherInfo{

    int tec_id;

    QString tec_name;

    QDate tec_birthday;

    QString tec_user;

    QString tec_account;

    QString tec_sex;

    QDate tec_joindate;

}TeacherInfo;

typedef struct ClassInfo{

    int class_id;

    QString class_name;

    QString class_grade;

    QString class_teacher;

}ClassInfo;

#endif // ACCOUNTINFO_H

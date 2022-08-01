#ifndef EXPORTEXCEL_H
#define EXPORTEXCEL_H

#include <QObject>
#include <QAxObject>

//#include "service/TeacherService.h"
//#include "service/StudentService.h"
class ExportExcel : public QObject{
    Q_OBJECT
public:
    explicit ExportExcel(QObject *parent = nullptr);

    /**
     * @brief 导出教师学期综合评价表
     * @param tec_id
     * @param term
     * @param fileName
     */
    bool exportTeacherEval(int tec_id,QString term,QString fileName);

    /**
     * @brief exportAllTeacherEval
     * @param term
     * @param fileName
     */
    bool exportAllTeacherEval(QString term,QString fileName);

    /**
     * @brief 导出某学生某学期综合评价表
     * @param stu_id
     * @param term
     * @param fileName
     */
    bool exportStudentEval(int stu_id,QString term,QString fileName);

    /**
     * @brief 导出某学生所在班级整体综合评价表
     * @param stu_id
     * @param term
     * @param fileName
     */
    bool exportStudentByClassEval(int stu_id,QString term,QString fileName);

private:

    QAxObject * sheet(QString fileName,QAxObject ** pApplication =0,QAxObject ** pWorkbook = nullptr);

private:

    //StudentService m_stuService;

    //TeacherService m_tecService;
};

#endif // EXPORTEXCEL_H

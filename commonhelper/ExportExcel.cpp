//#include "ExportExcel.h"
//#include <QDir>

//#include <QMessageBox>
//ExportExcel::ExportExcel(QObject *parent) : QObject(parent)
//{

//}

//bool ExportExcel::exportTeacherEval(int tec_id, QString term, QString fileName)
//{
//    QAxObject *pApplication = nullptr;
//    QAxObject *pWorkBook = nullptr;
//    QAxObject * pSheet = sheet(fileName, &pApplication, &pWorkBook);

//    if(!pApplication || !pWorkBook || !pSheet)
//    {
//        QMessageBox::warning(nullptr, "错误", "excel打开失败,请确认excel已经正确安装", "确定");
//        return false;
//    }

//    QList<QVariantMap> infos = m_tecService.getEvalByMonth(term,tec_id);

//    QStringList labels;

//    QStringList keys;

//    labels<<"学管教师姓名"	<<"性别"<<"出生年月"<<"隶属部门"<<"所带班级"<<"参加工作时间"<<"班级建设评价"<<"科研成果评价"<<"理论学习能力评价"<<"思想教育能力评价"<<"组织协调能力评价"<<"师德评价"<<"工作作风评价"<<"工作责任心评价"<<"创新意识评价"<<"总评分"<<"总体评价";
//    keys<<"tec_name"<<"tec_sex"<<"tec_birthday"<<"dep_name"<<"class_name"<<"tec_joindate"<<"班级建设评价"<<"科研成果评价"<<"理论学习能力评价"<<"思想教育能力评价"<<"组织协调能力评价"<<"师德评价"<<"工作作风评价"<<"工作责任心评价"<<"创新意识评价"<<"total"<<"tte_comment";

//    for(int i = 0 ;i < labels.size();i++)
//    {
//        //写入数据
//        QString& label = labels[i];
//        QAxObject *pRange = pSheet->querySubObject("Cells(int,int)", 1, i + 1);
//        pRange->dynamicCall("Value", label);
//    }

//    for(int i = 0; i< infos.size();i++)
//    {
//        QVariantMap & info = infos[i];
//        for(int j =0 ; j< keys.size();j++)
//        {
//            QVariant data = info[keys[j]];
//            QAxObject *pRange = pSheet->querySubObject("Cells(int,int)", i + 2, j + 1);
//            pRange->dynamicCall("Value", data.toString());
//        }
//    }

//    //保存
//    pWorkBook->dynamicCall("SaveAs(const QString &)", QDir::toNativeSeparators(fileName));
//    pApplication->dynamicCall("Quit()");
//    delete pApplication;
//    pApplication = nullptr;
//    return true;
//}

//bool ExportExcel::exportAllTeacherEval(QString term, QString fileName)
//{
//    QAxObject *pApplication = nullptr;
//    QAxObject *pWorkBook = nullptr;
//    QAxObject * pSheet = sheet(fileName,&pApplication,&pWorkBook);

//    if(!pApplication || !pWorkBook || !pSheet)
//    {
//        QMessageBox::warning(nullptr, "错误", "excel打开失败,请确认excel已经正确安装", "确定");
//        return false;
//    }

//    QList<QVariantMap> infos = m_tecService.getEvalByMonth(term);

//    QStringList labels;

//    QStringList keys;

//    labels<<"学管教师姓名"	<<"性别"<<"出生年月"<<"隶属部门"<<"所带班级"<<"参加工作时间"<<"班级建设评价"<<"科研成果评价"<<"理论学习能力评价"<<"思想教育能力评价"<<"组织协调能力评价"<<"师德评价"<<"工作作风评价"<<"工作责任心评价"<<"创新意识评价"<<"总评分"<<"总体评价";
//    keys<<"tec_name"<<"tec_sex"<<"tec_birthday"<<"dep_name"<<"class_name"<<"tec_joindate"<<"班级建设评价"<<"科研成果评价"<<"理论学习能力评价"<<"思想教育能力评价"<<"组织协调能力评价"<<"师德评价"<<"工作作风评价"<<"工作责任心评价"<<"创新意识评价"<<"total"<<"tte_comment";

//    for(int i = 0 ;i < labels.size();i++)
//    {
//        //写入数据
//        QString& label = labels[i];
//        QAxObject *pRange = pSheet->querySubObject("Cells(int,int)", 1, i + 1);
//        pRange->dynamicCall("Value", label);
//    }

//    for(int i = 0; i< infos.size();i++)
//    {
//        QVariantMap & info = infos[i];

//        for(int j =0 ; j< keys.size();j++)
//        {
//            QVariant data = info[keys[j]];
//            QAxObject *pRange = pSheet->querySubObject("Cells(int,int)", i + 2, j + 1);
//            pRange->dynamicCall("Value", data.toString());
//        }
//    }

//    //保存
//    pWorkBook->dynamicCall("SaveAs(const QString &)", QDir::toNativeSeparators(fileName));
//    pApplication->dynamicCall("Quit()");
//    delete pApplication;
//    pApplication = nullptr;
//    return true;
//}

//bool ExportExcel::exportStudentEval(int stu_id,QString term, QString fileName)
//{

//    QAxObject *pApplication = nullptr;
//    QAxObject *pWorkBook = nullptr;
//    QAxObject * pSheet = sheet(fileName,&pApplication,&pWorkBook);

//    if(!pApplication || !pWorkBook || !pSheet)
//    {
//        QMessageBox::warning(nullptr, "错误","excel打开失败,请确认excel已经正确安装", "确定");
//        return false;
//    }

//    QList<QVariantMap> infos = m_stuService.getStuEvalByTerm(term,stu_id);

//    QStringList labels;

//    QStringList keys;

//    labels<<"学生姓名"<<"性别"<<"系别"<<"专业"<<"班级"<<"学号"<<"学生获奖、评优情况评价（加分项）"<<"学生违纪情况评价（减分项）"<<"总评分"<<"总体评价"<<"学管教师姓名";

//    keys<<"stu_name"<<"stu_sex"<<"dep_name"<<"major_name"<<"class_name"<<"stu_idcard"<<"获奖评优情况评价"<<"违纪情况评价"<<"total"<<"tte_comment"<<"tec_name";

//    for(int i = 0 ;i < labels.size();i++)
//    {
//        //写入数据
//        QString& label = labels[i];
//        QAxObject *pRange = pSheet->querySubObject("Cells(int,int)", 1, i + 1);
//        pRange->dynamicCall("Value", label);
//    }

//    for(int i = 0; i< infos.size();i++)
//    {
//        QVariantMap & info = infos[i];
//        for(int j =0 ; j< keys.size();j++)
//        {
//            QVariant data = info[keys[j]];
//            QAxObject *pRange = pSheet->querySubObject("Cells(int,int)", i + 2, j + 1);
//            pRange->dynamicCall("Value", data.toString());
//        }
//    }
//    //保存
//    pWorkBook->dynamicCall("SaveAs(const QString &)", QDir::toNativeSeparators(fileName));
//    pApplication->dynamicCall("Quit()");
//    delete pApplication;
//    pApplication = nullptr;
//    return true;
//}

//bool ExportExcel::exportStudentByClassEval(int stu_id, QString term, QString fileName)
//{
//    int class_id = m_stuService.getClassIdByStuId(stu_id);
//    QAxObject *pApplication = nullptr;
//    QAxObject *pWorkBook = nullptr;
//    QAxObject * pSheet = sheet(fileName,&pApplication,&pWorkBook);

//    if(!pApplication || !pWorkBook || !pSheet)
//    {
//        QMessageBox::warning(nullptr, "错误", "excel打开失败,请确认excel已经正确安装", "确定");
//        return false;
//    }


//    QList<QVariantMap> infos = m_stuService.getEvalByMonth(term,class_id);

//    QStringList labels;

//    QStringList keys;


//    labels<<"学生姓名"<<"性别"<<"系别"<<"专业"<<"班级"<<"学号"<<"学生获奖、评优情况评价（加分项）"<<"学生违纪情况评价（减分项）"<<"总评分"<<"总体评价"<<"学管教师姓名";



//    keys<<"stu_name"<<"stu_sex"<<"dep_name"<<"major_name"<<"class_name"<<"stu_idcard"<<"获奖评优情况评价"<<"违纪情况评价"<<"total"<<"tte_comment"<<"tec_name";



//    for(int i = 0 ;i < labels.size();i++)
//    {
//        //写入数据

//        QString& label = labels[i];

//        QAxObject *pRange = pSheet->querySubObject("Cells(int,int)", 1, i + 1);

//        pRange->dynamicCall("Value", label);

//    }



//    for(int i = 0; i< infos.size();i++)
//    {


//        QVariantMap & info = infos[i];


//        for(int j =0 ; j< keys.size();j++)
//        {


//            QVariant data = info[keys[j]];


//            QAxObject *pRange = pSheet->querySubObject("Cells(int,int)", i + 2, j + 1);

//            pRange->dynamicCall("Value", data.toString());

//        }


//    }


//    //保存


//    pWorkBook->dynamicCall("SaveAs(const QString &)", QDir::toNativeSeparators(fileName));


//    pApplication->dynamicCall("Quit()");

//    delete pApplication;

//    pApplication = nullptr;

//    return true;

//}

//QAxObject *ExportExcel::sheet(QString fileName, QAxObject **pApplication_out, QAxObject **pWorkbook_out)
//{

//    QAxObject *pApplication = nullptr;
//    QAxObject *pWorkBooks = nullptr;
//    QAxObject *pWorkBook = nullptr;
//    QAxObject *pSheets = nullptr;
//    QAxObject *pSheet = nullptr;


//    pApplication = new QAxObject();
//    pApplication->setControl("Excel.Application");//连接Excel控件
//    pApplication->dynamicCall("SetVisible(bool)", false);//false不显示窗体
//    pApplication->setProperty("DisplayAlerts", false);//不显示任何警告信息。
//    pWorkBooks = pApplication->querySubObject("Workbooks");
//    QFile file(fileName);
//    if (file.exists())
//    {
//        pWorkBook = pWorkBooks->querySubObject("Open(const QString &)", fileName);
//    }
//    else
//    {
//        pWorkBooks->dynamicCall("Add");
//        pWorkBook = pApplication->querySubObject("ActiveWorkBook");
//    }
//    pSheets = pWorkBook->querySubObject("Sheets");
//    pSheet = pSheets->querySubObject("Item(int)", 1);

//    if(pApplication_out)
//    {
//        *pApplication_out = pApplication;
//    }

//    if(pWorkbook_out)
//    {
//        *pWorkbook_out = pWorkBook;
//    }

//    return pSheet;
//}

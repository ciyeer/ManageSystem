#include "adminwidget.h"
#include "ui_adminwidget.h"
#include <QMessageBox>
#include <QSqlRecord>
#include <QDebug>
#include <QTableWidgetItem>
#include <QSqlError>

AdminWidget::AdminWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWidget){
    ui->setupUi(this);
    m_bModifyFlag = false;
    connection();
    setUpTableView();
    setTableViewContextMenu();
}

void AdminWidget::connection(){
    connect(ui->adduserbtn, &QPushButton::clicked,
            this, &AdminWidget::slotAddUser);
    connect(ui->deleteuserbtn, &QPushButton::clicked,
            this, &AdminWidget::slotDeleteUser);
    connect(ui->modifyBtn, &QPushButton::clicked,
            this, &AdminWidget::slotModifyUserInfo);
    connect(ui->serachuser, &QPushButton::clicked,
            this, &AdminWidget::slotQueryUser);
    connect(ui->saveBtn, &QPushButton::clicked,
            this, &AdminWidget::slotSaveUserInfo);
    connect(ui->exitBtn, &QPushButton::clicked,
            this, &AdminWidget::slotReturnLoginWidget);
    connect(ui->user_tableView, &QTableView::customContextMenuRequested, this, &AdminWidget::slotDeleteContextMenu);
}

void AdminWidget::setTableViewContextMenu(){
    tableviewMenu = new QMenu(ui->user_tableView);
    deleteAction = new QAction("删除信息");
    tableviewMenu->addAction(deleteAction);
    connect(deleteAction,SIGNAL(triggered()),this,SLOT(slotDeleteUser()));
}

void AdminWidget::setUpTableView(){
    m_pModel = new QSqlTableModel(this);
    m_pModel->setTable("t_user");
    ui->user_tableView->setModel(m_pModel);
    m_pModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_pModel->select();
    ui->user_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pModel->sort(0, Qt::AscendingOrder); // 第0列升序排序

    // grid原本就是有多少格显示多少格，
    //    ui->tableView->setShowGrid(false); // 可隐藏grid
    // 右键点击
    ui->user_tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    // 只能单选
    ui->user_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    // 以行作为选择标准
    ui->user_tableView->setSelectionBehavior(QAbstractItemView::QAbstractItemView::SelectRows);
    // 行头隐藏
    ui->user_tableView->verticalHeader()->hide();
    // 让列头可被点击，触发点击事件
    ui->user_tableView->horizontalHeader()->setSectionsClickable(true);
    // 去掉选中表格时，列头的文字高亮
    ui->user_tableView->horizontalHeader()->setHighlightSections(false);
    ui->user_tableView->horizontalHeader()->setBackgroundRole(QPalette::Background);
    // 列头灰色
    // ui->user_tableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(225,225,225)};");
    connect(ui->user_tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortByColumn(int)));
}

// QTableView修改一行的保存操作
void AdminWidget::slotFlushUserInfo(){
#if 0
    QSqlTableModel *pMode = dynamic_cast<QSqlTableModel *>(ui->user_tableView->model());
    pMode->database().transaction();        // 开始事务操作
    if (pMode->submitAll()){                // 提交所有被修改的数据到数据库中
        pMode->database().commit();         // 提交成功，事务将真正修改数据库数据
    } else {
        pMode->database().rollback();       // 提交失败，事务回滚
        QMessageBox::warning(this, tr("tableModel"),tr("数据库错误: %1").arg(pMode->lastError().text()));
    }
    pMode->revertAll(); // 撤销修改
#endif

    m_pModel->database().transaction();        // 开始事务操作
    if (m_pModel->submitAll()){                // 提交所有被修改的数据到数据库中
        m_pModel->database().commit();         // 提交成功，事务将真正修改数据库数据
    } else {
        m_pModel->database().rollback();       // 提交失败，事务回滚
        QMessageBox::warning(this, tr("tableModel"),tr("数据库错误: %1").arg(m_pModel->lastError().text()));
    }
    m_pModel->revertAll(); // 撤销修改
}

// QTableView新增一行的操作
void AdminWidget::slotAddUser(){
#if 0
    if(!m_bModifyFlag)
        return;
    QSqlTableModel *pMode = dynamic_cast<QSqlTableModel *>(ui->user_tableView->model());
    QSqlRecord record = pMode->record();
    pMode->setRecord(pMode->rowCount(), record);
    // 将表格的编辑模式打开
    ui->user_tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    int number;
    // 从1开始遍历，遇到相同的，自增再遍历，直到没有相同的作为number插入
    // 防止唯一主键重复导致提交失败，因为提交失败tableview还是会更新修改后的（视图）
    for(number = 1; ; number++){
        bool bFlag = false;
        for(int index = 0; index < pMode->rowCount(); index++) {
            if(pMode->index(index, 0).data().toInt() == number) {
                bFlag = true;
                break;
            }
        }
        if(!bFlag) {
            break;
        }
    }

    pMode->insertRecord(pMode->rowCount(), record);
    // 每次手动提交，都会重新刷新tableView，保持mode和tableView一致
    pMode->submitAll();
#endif
    if(!m_bModifyFlag)
        return;

    QSqlRecord record = m_pModel->record();
    m_pModel->setRecord(m_pModel->rowCount(), record);
    // 将表格的编辑模式打开
    ui->user_tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    int number;
    // 从1开始遍历，遇到相同的，自增再遍历，直到没有相同的作为number插入
    // 防止唯一主键重复导致提交失败，因为提交失败tableview还是会更新修改后的（视图）
    for(number = 1; ; number++){
        bool bFlag = false;
        for(int index = 0; index < m_pModel->rowCount(); index++) {
            if(m_pModel->index(index, 0).data().toInt() == number) {
                bFlag = true;
                break;
            }
        }
        if(!bFlag) {
            break;
        }
    }

    m_pModel->insertRecord(m_pModel->rowCount(), record);
    // 每次手动提交，都会重新刷新tableView，保持mode和tableView一致
    m_pModel->submitAll();
}

// 删除用户
void AdminWidget::slotDeleteUser(){
#if 0
    if(!m_bModifyFlag)
        return;
    //设置表格的单元为只读属性，即不能编辑
    ui->user_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //如果你用在QTableView中使用右键菜单，需启用该属性
    ui->user_tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    QSqlTableModel *pMode = dynamic_cast<QSqlTableModel *>(ui->user_tableView->model());
    // 当QSqlTableModel::EditStrategy 选择 非QSqlTableModel::OnManualSubmit 时,
    // 每次删除都可删除掉model，但是tableview那一列为空，一直在，只好设置为 QSqlTableModel::OnManualSubmit
    pMode->removeRow(ui->user_tableView->currentIndex().row());
    // 每次手动提交，都会重新刷新tableView，保持mode和tableView一致
    pMode->submitAll();
#endif
    if(!m_bModifyFlag)
        return;
    //设置表格的单元为只读属性，即不能编辑
    ui->user_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //如果你用在QTableView中使用右键菜单，需启用该属性
    ui->user_tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    // 当QSqlTableModel::EditStrategy 选择 非QSqlTableModel::OnManualSubmit 时,
    // 每次删除都可删除掉model，但是tableview那一列为空，一直在，只好设置为 QSqlTableModel::OnManualSubmit
    m_pModel->removeRow(ui->user_tableView->currentIndex().row());
    // 每次手动提交，都会重新刷新tableView，保持mode和tableView一致
    m_pModel->submitAll();
}

void AdminWidget::sortByColumn(int col){
#if 0
    QSqlTableModel *pMode = dynamic_cast<QSqlTableModel *>(ui->user_tableView->model());
    bool ascending = (ui->user_tableView->horizontalHeader()->sortIndicatorSection()==col
                      && ui->user_tableView->horizontalHeader()->sortIndicatorOrder()==Qt::DescendingOrder);
    Qt::SortOrder order = ascending ? Qt::AscendingOrder : Qt::DescendingOrder;
    pMode->sort(col, order);
#endif
    bool ascending = (ui->user_tableView->horizontalHeader()->sortIndicatorSection()==col
                      && ui->user_tableView->horizontalHeader()->sortIndicatorOrder()==Qt::DescendingOrder);
    Qt::SortOrder order = ascending ? Qt::AscendingOrder : Qt::DescendingOrder;
    m_pModel->sort(col, order);
}

void AdminWidget::slotDeleteContextMenu(const QPoint pos){
    if(!m_bModifyFlag)
        return;
    QModelIndex index = ui->user_tableView->indexAt(pos);
    // 模型中有数据时，即模型索引可以获取到，根据选中的函数是否大于一判断出现菜单1还是菜单2
    if(index.isValid())     {
        QItemSelectionModel *selections =  ui->user_tableView->selectionModel();    // 获取被选中的指针列表
        QModelIndexList selected = selections->selectedIndexes();
        QMap <int, int> rowMap;
        foreach (QModelIndex index, selected){
            rowMap.insert(index.row(), 0); // QModelIndex 有更多数据可用
        }

        if(rowMap.count() == 1){
            // 当只选中了一行时弹出菜单1
            deleteAction->setEnabled(true);
            tableviewMenu->exec(QCursor::pos());
        }
        else{
//            // 选中多行时，弹出菜单2
//            num1 = rowMap.firstKey();   // 要操作的数据起始行
//            num2 = rowMap.count();      // 要操作的数据的行数
//            tableviewMenu->exec(QCursor::pos());
        }
    }
    else{    //模型中没有数据时，即模型索引获取不到，出现菜单一
        deleteAction->setEnabled(false);
        tableviewMenu->exec(QCursor::pos());//菜单出现位置为鼠标右键点击的位置
    }
}

void AdminWidget::slotQueryUser(){
//    QSqlTableModel *pMode = dynamic_cast<QSqlTableModel *>(ui->user_tableView->model());
//    pMode->setFilter(ui->queryLineEdit->text());
    if(ui->queryLineEdit->text().isEmpty()){
        //m_pModel->setTable("t_user");
        m_pModel->select();
        return;
    }

    // m_pModel->setFilter(QString("user_account = '%1'").arg(ui->queryLineEdit->text()));
    m_pModel->setFilter(QString("user_account like '%%1%'").arg(ui->queryLineEdit->text()));
    m_pModel->select();
}
#if 0
void serch(){
    QString name = ui->lineEdit_7->text();
        QString author=ui->lineEdit_8->text();
        QSqlQuery query;//复习：一个操作数据库的工具
        int count=0,count2=0;
        //判断输入情况，是否为空
        if(name.length()!=0&&author.length()==0){
        //采用的模糊查询，只要结果包含输入，就会被查出来
            model->setFilter(QString("name like '%%1%'").arg(name));//一个舍去了“select”关键词的筛选函数
            model->select();
            QString sql=QString("select * from books where name like '%%1%'").arg(name);//复习：写出SQL语句
            query.exec(sql);//复习：执行这条SQL语句
            while(query.next())//复习：循环查询结果集，进行一系列操作
            {
                count++;//对查询结果计数
                if(query.value(7).toString()=="未借出"){
                    count2++;//对在馆数量计数
                }

            }
            //这里要进行类型的转换，把int转化为QString，因为label\lineEdit这种都默认显示QString类型的数据
            QString str_count=QString::number(count);
            QString str_count2=QString::number(count2);
            ui->label_4->setText(str_count);
            ui->label_5->setText(str_count2);
        }else if(author.length()!=0&&name.length()==0){
        //以下同理
            model->setFilter(QString("author like '%%2%'").arg(author));
            model->select();
            QString str_count=QString::number(count);
            QString str_count2=QString::number(count2);
            ui->label_4->setText(str_count);
            ui->label_5->setText(str_count2);
        }else if(name.length()!=0&&author.length()!=0){
            model->setFilter(QString("name like '%%1%' && author like '%%2%'").arg(name).arg(author));
            model->select();
            QString sql=QString("select * from books where name like '%%1%'&& author like '%%2%'").arg(name).arg(author);
            query.exec(sql);
            while(query.next())
            {
                count++;
                if(query.value(7).toString()=="未借出"){
                    count2++;
                }

            }
            QString str_count=QString::number(count);
            QString str_count2=QString::number(count2);
            ui->label_4->setText(str_count);
            ui->label_5->setText(str_count2);
        }
}
#endif

void AdminWidget::slotModifyUserInfo(){
    m_bModifyFlag = true;
    // 将表格的编辑模式打开
    ui->user_tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
}

void AdminWidget::slotSaveUserInfo(){
    m_bModifyFlag = false;
    //设置表格的单元为只读属性，即不能编辑
    ui->user_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pModel->submitAll();
}

void AdminWidget::slotReturnLoginWidget(){
    emit display(0);
}

AdminWidget::~AdminWidget(){
    delete ui;
}






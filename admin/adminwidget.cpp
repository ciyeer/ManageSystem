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
    if(ui->queryLineEdit->text().isEmpty()){
        m_pModel->setFilter(ui->queryLineEdit->text());
        m_pModel->select();
        return;
    }

    m_pModel->setFilter(QString("user_account like '%%1%'").arg(ui->queryLineEdit->text()));
    m_pModel->select();
}

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






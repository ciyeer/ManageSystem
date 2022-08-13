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

    connection();
    setUpTableView();    
}

void AdminWidget::connection(){
    connect(ui->adduserbtn, &QPushButton::clicked,
            this, &AdminWidget::slotAddUser);
    connect(ui->deleteuserbtn, &QPushButton::clicked,
            this, &AdminWidget::slotDeleteUser);
    connect(ui->modifyBtn, &QPushButton::clicked,
            this, &AdminWidget::slotModifyUserInfo);
//    connect(ui->serachuser, &QPushButton::clicked,
//            this, &AdminWidget::slotQueryUser);
//    connect(ui->flushBtn, &QPushButton::clicked,
//            this, &AdminWidget::slotClearUserInfo);
    connect(ui->exitBtn, &QPushButton::clicked,
            this, &AdminWidget::slotReturnLoginWidget);
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
    // connect(ui->user_tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortByColumn(int)));
}

// QTableView修改一行的保存操作
void AdminWidget::slotFlushUserInfo(){
    QSqlTableModel *pMode = dynamic_cast<QSqlTableModel *>(ui->user_tableView->model());
    pMode->database().transaction();        // 开始事务操作
    if (pMode->submitAll())                 // 提交所有被修改的数据到数据库中
    {
        pMode->database().commit();         // 提交成功，事务将真正修改数据库数据
    } else {
        pMode->database().rollback();       // 提交失败，事务回滚
        QMessageBox::warning(this, tr("tableModel"),tr("数据库错误: %1").arg(pMode->lastError().text()));
    }
    pMode->revertAll(); // 撤销修改
}

// QTableView新增一行的操作
void AdminWidget::slotAddUser(){
    QSqlTableModel *pMode = dynamic_cast<QSqlTableModel *>(ui->user_tableView->model());
    QSqlRecord record = pMode->record();
    pMode->setRecord(pMode->rowCount(), record);
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
}

// 删除用户
void AdminWidget::slotDeleteUser(){
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
}

void AdminWidget::sortByColumn(int col){
    QSqlTableModel *pMode = dynamic_cast<QSqlTableModel *>(ui->user_tableView->model());
    bool ascending = (ui->user_tableView->horizontalHeader()->sortIndicatorSection()==col
                      && ui->user_tableView->horizontalHeader()->sortIndicatorOrder()==Qt::DescendingOrder);
    Qt::SortOrder order = ascending ? Qt::AscendingOrder : Qt::DescendingOrder;
    pMode->sort(col, order);
}

void AdminWidget::slotQueryUser(){
    QueryUserInfoDialog queryDlg;
    queryDlg.exec();
}

void AdminWidget::slotModifyUserInfo(){
    // 将表格的编辑模式打开
    ui->user_tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
}

void AdminWidget::slotClearUserInfo(){
    ClearUserInfoDialog clearDlg;
    clearDlg.exec();
}


void AdminWidget::slotReturnLoginWidget(){
    emit display(0);
}

AdminWidget::~AdminWidget(){
    delete ui;
}






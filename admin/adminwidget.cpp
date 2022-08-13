#include "adminwidget.h"
#include "ui_adminwidget.h"

AdminWidget::AdminWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWidget){
    ui->setupUi(this);

    // connection();
    setUpTableView();
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
    connect(ui->flushBtn, &QPushButton::clicked,
            this, &AdminWidget::slotClearUserInfo);
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

void AdminWidget::slotAddUser(){
    AddUserInfoDialog addDlg;
    addDlg.exec();
}

void AdminWidget::slotQueryUser(){
    QueryUserInfoDialog queryDlg;
    queryDlg.exec();
}

void AdminWidget::slotDeleteUser(){
    deleteUserInfoDialog deleteDlg;
    deleteDlg.exec();
}

void AdminWidget::slotModifyUserInfo(){
    ModifyUserInfoDialog modifyDlg;
    modifyDlg.exec();
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





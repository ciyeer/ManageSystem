#include "statusbar.h"
#include "ui_statusbar.h"

StatusBar::StatusBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusBar){
    ui->setupUi(this);
    m_pWarnLabelTimer = new QTimer(this);
    connect(m_pWarnLabelTimer, &QTimer::timeout,
            this, &StatusBar::slotClearWarnningLabel);
}

void StatusBar::slotRecieveMsg(QString strMsg){
    ui->warningLabel->setText(strMsg);
}

void StatusBar::slotClearWarnningLabel(){
    ui->warningLabel->clear();
}

void StatusBar::slotEmitTimerSignal(){
    m_pWarnLabelTimer->start(3000); // 3s之后清空警告
}

StatusBar::~StatusBar()
{
    delete ui;
}

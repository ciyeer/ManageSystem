#include "cmessagebox.h"
#include "ui_cmessagebox.h"
#include <QPainter>
#include <QCloseEvent>
#include <QDebug>

CMessageBox::CMessageBox(QWidget *parent) :
    QWidget(parent),
    m_eventLoop(NULL),
    m_chooseResult(ID_CANCEL),
    ui(new Ui::CMessageBox){
    ui->setupUi(this);

    // 设置标题栏跑马灯效果，可以不设置;
    //m_titleBar->setTitleRoll();
//    m_titleBar->setTitleIcon(":/winIcon");
//    m_titleBar->setTitleContent(QStringLiteral("确认删除"));
//    m_titleBar->setButtonType(MIN_MAX_CLOSE_SETTING_BUTTON);
//    m_titleBar->setTitleWidth(this->width());

    initWindow();
}

CMessageBox::~CMessageBox(){
    delete ui;
}

void CMessageBox::loadStyleSheet(const QString &strpath){
    QFile file(strpath);
    if(!file.open(QIODevice::ReadOnly))
        qDebug() << "Open File Failed!";
    this->setStyleSheet(file.readAll());
    file.close();
}

void CMessageBox::initWindow(){
    this->setWindowFlag(Qt::FramelessWindowHint);
    // loadStyleSheet(":/msgbox");
    Qt::WindowFlags flags = this->windowFlags();
    this->setWindowFlags(flags | Qt::Window);

    ui->inputContent->setVisible(false);

    connect(ui->pButtonOk, SIGNAL(clicked()), this, SLOT(onOkClicked()));
    connect(ui->pButtonCancel, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
}

void CMessageBox::paintEvent(QPaintEvent *event){
    // 绘制窗口白色背景色;
    QPainter painter(this);
    QPainterPath pathBack;
    pathBack.setFillRule(Qt::WindingFill);
    pathBack.addRect(QRect(0, 0, this->width(), this->height()));
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.fillPath(pathBack, QBrush(QColor(255, 255, 255)));

    // 绘制按钮部分灰色背景;
    QPainterPath pathButtonBack;
    pathButtonBack.setFillRule(Qt::WindingFill);
    pathButtonBack.addRect(QRect(0, 110, this->width(), 48));
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.fillPath(pathButtonBack, QBrush(QColor(247, 247, 247)));

    // 绘制窗口灰色边框;
    QPen pen(QColor(204, 204, 204));
    painter.setPen(pen);
    painter.drawRect(0, 0, this->width() - 1, this->height() - 1);

    // 绘制窗口上方蓝条;
//    QPainterPath pathHead;
//    pathHead.setFillRule(Qt::WindingFill);
//    pathHead.addRect(QRect(0, 0, this->width(), 2));
//    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
//    painter.fillPath(pathHead, QBrush(QColor(15, 151, 255)));

    return QWidget::paintEvent(event);
}

void CMessageBox::setWindowTitle(QString title, int titleFontSize){
    // m_titleBar->setTitleContent(title, titleFontSize);
}

void CMessageBox::setContentText(QString contentText){
    ui->MessageContent->setText(contentText);
}

void CMessageBox::setMessageType(MessageType messageType){
    switch (messageType){
    case MESSAGE_INFORMATION:
        ui->MessageIcon->setPixmap(QPixmap(":/information"));
        break;
    case MESSAGE_WARNNING:
        ui->MessageIcon->setPixmap(QPixmap(":/warnning"));
        break;
    case MESSAGE_QUESTION:
        ui->MessageIcon->setPixmap(QPixmap(":/question"));
        break;
    case MESSAGE_INPUT:
        ui->MessageIcon->setVisible(false);
        ui->inputContent->setVisible(true);
    case MESSAGE_NONE:
        ui->MessageIcon->setVisible(false);
    default:
        break;
    }
}

void CMessageBox::setButtonType(MessageButtonType buttonType){
    switch (buttonType){
    case BUTTON_OK:{
        ui->pButtonOk->setText(QStringLiteral("确定"));
        ui->pButtonCancel->setVisible(false);
        break;
    }       
    case BUTTON_OK_AND_CANCEL:{
        ui->pButtonOk->setText(QStringLiteral("确定"));
        ui->pButtonCancel->setText(QStringLiteral("取消"));
        break;
    }       
    default:
        break;
    }
}

void CMessageBox::setMessageContent(QString messageContent){
    ui->MessageContent->setText(messageContent);
}

// 显示提示框
// isModelWindow 参数设置提示框是否是模态
int CMessageBox::showCMessageBox(QWidget* parent,
                                 const QString &title,
                                 const QString &contentText,
                                 MessageType messageType,
                                 MessageButtonType messageButtonType,
                                 bool isModelWindow){
    CMessageBox * myMessageBox = new CMessageBox(parent);
    myMessageBox->setWindowTitle(title);
    myMessageBox->setContentText(contentText);
    myMessageBox->setMessageType(messageType);
    myMessageBox->setButtonType(messageButtonType);
    if (isModelWindow){
        // 设置为模态窗口时，参数parent必须设置父窗口指针，否则模态设置无效;
        // 因为 Qt::WindowModal 参数只对父窗口有效，如果想要模态对全局窗口都有效可以设置 Qt::ApplicationModal
        return myMessageBox->exec();
    }
    else
        myMessageBox->show();

    return 0;
}

int CMessageBox::exec(){
    // 因为QWidget没有exec()方法，所以需要自己定义来完成exec()方法;
    // 而exec()方法就是直接设置窗口显示为模态，并且窗口关闭结束后返回用户选择结果(按了确定还是取消按钮);
    // 而show()方法只是显示窗口，并不会设置窗口的模态或者非模态，需要自己调用setWindowModality()方法进行设置;
    // 而且show()方法并不会返回用户选择结果;
    // 这里也可以继承QDialog类，QDialog有自己的exec()方法，根据返回 Accepted, Rejected来决定是否按了确定按钮;
    // 设置为窗口级模态，也可设置为应用程序及模态 Qt::ApplicationModal;
    this->setWindowModality(Qt::WindowModal);
    this->show();
    // 使用事件循环QEventLoop ,不让exec()方法结束，在用户选择确定或者取消后，关闭窗口结束事件循环，并返回最后用户选择的结果;
    // 根据返回结果得到用户按下了确定还是取消，采取相应的操作。从而模拟出QDialog类的exec()方法;
    m_eventLoop = new QEventLoop(this);
    m_eventLoop->exec();

    return m_chooseResult;
}

void CMessageBox::onOkClicked(){
    m_chooseResult = ID_OK;
    close();
}

void CMessageBox::onCancelClicked(){
    m_chooseResult = ID_CANCEL;
    close();
}

void CMessageBox::closeEvent(QCloseEvent *event){
    // 关闭窗口时结束事件循环，在exec()方法中返回选择结果;
    if (m_eventLoop != NULL){
        m_eventLoop->exit();
    }
    event->accept();
}

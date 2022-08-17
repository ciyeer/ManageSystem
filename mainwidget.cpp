#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "commonhelper/commonhelper.h"
#include <QIcon>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget){
    ui->setupUi(this);
    m_bisPressed = false;
    setStyle(":/image/css/image.css");
    setWindowFlag(Qt::FramelessWindowHint);
    setWindowIcon(QIcon(":/image/icon/snipaste.png"));

    m_pStackedLayout = new QStackedLayout;

    m_pTitleBar    = new TitleBar;
    m_pStatusBar   = new StatusBar;

    m_pLoginWidget = new LoginWidget;
    m_pAdminWidget = new AdminWidget;
    m_pUserWidget  = new UserWidget;

    m_pStackedLayout->addWidget(m_pLoginWidget);
    m_pStackedLayout->addWidget(m_pAdminWidget);
    m_pStackedLayout->addWidget(m_pUserWidget);

    ui->titleLayout->addWidget(m_pTitleBar);
    ui->statusLayout->addWidget(m_pStatusBar);
    ui->centerLayout->addLayout(m_pStackedLayout);

    connect(m_pLoginWidget, &LoginWidget::display,
            m_pStackedLayout, &QStackedLayout::setCurrentIndex);
    connect(m_pAdminWidget, &AdminWidget::display,
            m_pStackedLayout, &QStackedLayout::setCurrentIndex);
    connect(m_pUserWidget, &UserWidget::display,
            m_pStackedLayout, &QStackedLayout::setCurrentIndex);
}

void MainWidget::setStyle(const QString &strPath){
    QFile file(strPath);
    if(!file.open(QFile::ReadOnly)){
        qDebug() << "load css file failed!";
        return;
    }
    QString styleSheet = QLatin1String(file.readAll());
    setStyleSheet(styleSheet);
    file.close();
}

void MainWidget::mouseMoveEvent(QMouseEvent *event){
    if(m_bisPressed){
        // 通过事件event->globalPos()知道鼠标坐标
        // 鼠标坐标减去鼠标相对于窗口位置，就是窗口在整个屏幕的坐标
        move(event->globalPos() - m_point); // 移动
    }
}

void MainWidget::mousePressEvent(QMouseEvent *event){
    // 鼠标左键
    if(event->button() == Qt::LeftButton){
        // event->globalPos() 鼠标按下时，鼠标相对于整个屏幕位置
        // this->pos() 鼠标按下时，窗口相对于整个屏幕位置
        // event->globalPos() - this->pos() 鼠标相对于窗口的位置
        m_point = event->globalPos() - this->pos();
        m_bisPressed = true;
        //m_bisPressed = m_areaMovable.contains(m_point);
    }
}

void MainWidget::mouseReleaseEvent(QMouseEvent *event){
    Q_UNUSED(event)
    m_bisPressed = false;
}


MainWidget::~MainWidget(){
    delete ui;
}

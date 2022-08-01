#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "commonhelper/commonhelper.h"
#include <QIcon>

MainWidget::MainWidget(MouseEvent *parent) :
    MouseEvent(parent),
    ui(new Ui::MainWidget){
    ui->setupUi(this);
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

MainWidget::~MainWidget(){
    delete ui;
}

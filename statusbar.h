#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class StatusBar;
}

class StatusBar : public QWidget{
    Q_OBJECT

public:
    explicit StatusBar(QWidget *parent = nullptr);
    ~StatusBar();

public slots:
    // 接收错误消息(从centerWidget中)
    void slotRecieveMsg(QString strMsg);
    void slotClearWarnningLabel();
    void slotEmitTimerSignal();

private:
    Ui::StatusBar *ui;
    QTimer *m_pWarnLabelTimer;  // 提示框的定时器
};

#endif // STATUSBAR_H

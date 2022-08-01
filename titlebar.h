#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>

namespace Ui {
class TitleBar;
}

class TitleBar : public QWidget{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();

public slots:
    void slotCloseWidget();         // 关闭界面槽
    void slotMiniSizedWidget();     // 最小化界面槽

private:
    Ui::TitleBar *ui;
};

#endif // TITLEBAR_H

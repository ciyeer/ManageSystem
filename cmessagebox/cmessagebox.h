#ifndef CMESSAGEBOX_H
#define CMESSAGEBOX_H

#include <QWidget>
#include <QEventLoop>

namespace Ui {
class CMessageBox;
}

enum ChosseResult{
    ID_OK = 0,                      // 确定;
    ID_CANCEL                       // 取消;
};

enum MessageType{
    MESSAGE_INFORMATION = 0,        // 提示信息;
    MESSAGE_WARNNING,               // 提示警告;
    MESSAGE_QUESTION,               // 提示询问;
    MESSAGE_INPUT,                  // 提示输入框;
    MESSAGE_NONE                    // 无提示图片
};

enum MessageButtonType{
    BUTTON_OK = 0,                  // 只有确定按钮;
    BUTTON_OK_AND_CANCEL,           // 确定、取消按钮;
    BUTTON_CLOSE                    // 关闭按钮;
};

class CMessageBox : public QWidget{
    Q_OBJECT

public:
    explicit CMessageBox(QWidget *parent = nullptr);
    ~CMessageBox();

    void setWindowTitle(QString title, int titleFontSize = 10);
    void setContentText(QString contentText);
    void setMessageType(MessageType messageType);
    void setButtonType(MessageButtonType buttonType);
    void setMessageContent(QString messageContent);

public:
    int static showCMessageBox(QWidget* parent, const QString &title,
                                const QString &contentText ,
                                MessageType messageType,
                                MessageButtonType messageButtonType ,
                                bool isModelWindow = false);

private:
    void initWindow();
    void initTitleBar();
    int exec();

    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);
    void loadStyleSheet(const QString &);

private slots:
    void onOkClicked();
    void onCancelClicked();

private:   
    QEventLoop* m_eventLoop;
    ChosseResult m_chooseResult;
    Ui::CMessageBox *ui;
};

#endif // CMESSAGEBOX_H

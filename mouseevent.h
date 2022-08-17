#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QRect>

class MouseEvent : public QWidget{
public:
    explicit MouseEvent(QWidget *parent = nullptr);
    void setAreaMovable(const QRect rt);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool m_bisPressed;
    QPoint m_point;     // 鼠标点击的坐标
    //QRect m_areaMovable;
};

#endif // MOUSEEVENT_H

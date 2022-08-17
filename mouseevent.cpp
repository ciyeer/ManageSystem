#include "mouseevent.h"
#include <QDebug>

MouseEvent::MouseEvent(QWidget *parent)
    : QWidget(parent){
    m_bisPressed = false;
    //m_areaMovable = geometry();
    //qDebug() << m_areaMovable;
}

void MouseEvent::mouseMoveEvent(QMouseEvent *event){
    if(m_bisPressed){
        // 通过事件event->globalPos()知道鼠标坐标
        // 鼠标坐标减去鼠标相对于窗口位置，就是窗口在整个屏幕的坐标
        move(event->globalPos() - m_point); // 移动
    }
}

void MouseEvent::mousePressEvent(QMouseEvent *event){
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

void MouseEvent::mouseReleaseEvent(QMouseEvent *event){
    Q_UNUSED(event)
    m_bisPressed = false;
}

//设置鼠标按下的区域
void MouseEvent::setAreaMovable(const QRect rt){
//    if(m_areaMovable != rt){
//        m_areaMovable = rt;
//    }
}

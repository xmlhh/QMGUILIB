/************************************************************************
*   文件名称：LDrawFilterWgt.h
*   编写人员：LHH
*   创建日期：2016/02/01
*   功能描述：重写窗口事件：实现窗口移动、弹簧拉伸缩放、鼠标指针形状、最大化、还原
*   备    注：
*   修改描述：
*   团    队：C++/Qt项目组
************************************************************************/

#ifndef LDRAWFILTERWGT_H
#define LDRAWFILTERWGT_H

#include <QObject>
#include <QtWidgets>
#include <QMouseEvent>

class LDrawFilterWgt : public QObject
{

    Q_OBJECT
        Q_PROPERTY(bool dragable READ isDragable WRITE setDragable)
        Q_PROPERTY(bool resizable READ isResizable WRITE setResizable)
        Q_PROPERTY(bool maxable READ isMaxable WRITE setMaxable)

public:
    LDrawFilterWgt(QObject *parent);
    ~LDrawFilterWgt();

public:
    enum CursorPos{CURSOR_ARROW, CURSOR_LEFT, CURSOR_LEFT_BOTTOM, CURSOR_BOTTOM, CURSOR_RIGHT_BOTTOM, CURSOR_RIGHT};

    // 设置是否可以拖动
    bool isDragable(){return m_bDragable;}
    void setDragable(bool bDragable){m_bDragable = bDragable;}

    // 设置是否可以缩放
    bool isResizable(){return m_bResizable;}
    void setResizable(bool bResizable){m_bResizable = bResizable;}

    // 设置窗口是否最大化
    bool isMaxable(){return m_bMaxable;}
    void setMaxable(bool bMaxable){m_bMaxable = bMaxable;}

    // 事件过滤器
    bool eventFilter(QObject *, QEvent *);

private:
    // 位置信息
    QPoint m_posDelta;
    QPoint m_posMouse;
    QRect m_oldGeometry;

    // 光标类型
    CursorPos m_cursorPos;
    // 鼠标左键按下
    bool m_bPressed;
    // 拖拽中
    bool m_bDrag;
    // 是否允许拖拽
    bool m_bDragable;
    // 伸缩中
    bool m_bResize;
    // 是否允许伸缩
    bool m_bResizable;
    // 窗口允许最大化
    bool m_bMaxable;
};

#endif // LDRAWFILTERWGT_H

#include "LDrawFilterWgt.h"

LDrawFilterWgt::LDrawFilterWgt(QObject *parent)
    :QObject(parent),
    m_cursorPos(CURSOR_ARROW),
    m_bPressed(false),
    m_bDrag(false),
    m_bDragable(true),
    m_bResize(false),
    m_bResizable(false),
    m_bMaxable(false)
{

}

LDrawFilterWgt::~LDrawFilterWgt()
{

}

bool LDrawFilterWgt::eventFilter(QObject *obj, QEvent *event)
{
    switch(event->type())
    {
    // 鼠标按下事件
    case QEvent::MouseButtonPress:
        {
            QMouseEvent *pMouseEvent = static_cast<QMouseEvent *>(event);
            QWidget *pWidget = qobject_cast<QWidget *>(obj);

            // 点击鼠标左键
            if (pMouseEvent->button() == Qt::LeftButton)
            {
                m_bPressed = true;
                m_posMouse = pMouseEvent->globalPos();
                m_oldGeometry = pWidget->geometry();

                if (m_bDragable && pMouseEvent->pos().y() < 35)
                {
                    // 只有点击到头部才能拖动
                    m_bDrag = true;
                    QPoint windowPos = pWidget->pos();
                    m_posDelta = m_posMouse - windowPos;
                }
            }
        }
        break;

    // 鼠标拖动事件
    case QEvent::MouseMove:
        {
            QMouseEvent *pMouseEvent = static_cast<QMouseEvent *>(event);
            QWidget* pWidget = qobject_cast<QWidget *>(obj);

            if (m_bDrag && (pMouseEvent->buttons() & Qt::LeftButton))
            {
                pWidget->move(pMouseEvent->globalPos() - m_posDelta);
            }
        }
        break;

    // 鼠标改变大小
    case QEvent::HoverMove:
        {
            QHoverEvent *pHoverEvent = static_cast<QHoverEvent *>(event);
            QWidget* pWidget = qobject_cast<QWidget *>(obj);
            QPoint pos = pHoverEvent->pos();
            if (m_bResizable && !m_bPressed)
            {
                m_bResize = true;

                if (pos.x() <= 10 && (pWidget->height() - pos.y() > 5))
                {
                    // 左侧
                    pWidget->setCursor(Qt::SizeHorCursor);
                    m_cursorPos = CURSOR_LEFT;
                }
                else if (pos.x() <= 5 && (pWidget->height() - pos.y() <= 5))
                {
                    // 左下角
                    pWidget->setCursor(Qt::SizeBDiagCursor);
                    m_cursorPos = CURSOR_LEFT_BOTTOM;
                }
                else if ((pWidget->height() - pos.y() <=5) && (pWidget->width() - pos.x() <= 5))
                {
                    // 右下角
                    pWidget->setCursor(Qt::SizeFDiagCursor);
                    m_cursorPos = CURSOR_RIGHT_BOTTOM;
                }
                else if (pWidget->height() - pos.y() <= 5)
                {
                    // 下侧
                    pWidget->setCursor(Qt::SizeVerCursor);
                    m_cursorPos = CURSOR_BOTTOM;
                }
                else if ((pWidget->width() - pos.x() <= 5))
                {
                    // 右侧
                    pWidget->setCursor(Qt::SizeHorCursor);
                    m_cursorPos = CURSOR_RIGHT;
                }
                else
                {
                    pWidget->setCursor(Qt::ArrowCursor);
                    m_cursorPos = CURSOR_ARROW;
                    m_bResize = false;
                }
            }

            if (m_bResizable && m_bResize && m_bPressed)
            {
                // 鼠标按下，且resize
                QPoint posDelta = pWidget->mapToGlobal(pHoverEvent->pos()) - m_posMouse;
                switch(m_cursorPos)
                {
                case CURSOR_LEFT:
                    {
                        int iWidth = m_oldGeometry.width() - posDelta.x();
                        int iX = m_oldGeometry.x() + posDelta.x();

                        if (iWidth < pWidget->minimumWidth())
                        {
                            iX = m_oldGeometry.x() + m_oldGeometry.width() - pWidget->minimumWidth();
                        }

                        pWidget->setGeometry(iX, m_oldGeometry.y(), iWidth, m_oldGeometry.height());
                    }
                    break;

                case CURSOR_RIGHT:
                    {
                        pWidget->setGeometry(m_oldGeometry.x(), m_oldGeometry.y(),
                            m_oldGeometry.width() + posDelta.x(), m_oldGeometry.height());
                    }
                    break;

                case CURSOR_LEFT_BOTTOM:
                    {
                        int iWidth = m_oldGeometry.width() - posDelta.x();
                        int iX = m_oldGeometry.x() + posDelta.x();

                        if (iWidth < pWidget->minimumWidth())
                        {
                            iX = m_oldGeometry.x() + m_oldGeometry.width() - pWidget->minimumWidth();
                        }
                        pWidget->setGeometry(iX, m_oldGeometry.y(), iWidth, m_oldGeometry.height() + posDelta.y());
                    }
                    break;

                case CURSOR_RIGHT_BOTTOM:
                    {
                        pWidget->setGeometry(m_oldGeometry.x(), m_oldGeometry.y(),
                            m_oldGeometry.width() + posDelta.x(), m_oldGeometry.height() + posDelta.y());
                    }
                    break;

                case CURSOR_BOTTOM:
                    {
                        pWidget->setGeometry(m_oldGeometry.x(), m_oldGeometry.y(),
                            m_oldGeometry.width(), m_oldGeometry.height() + posDelta.y());
                    }
                    break;

                default:
                    break;
                }
            }
        }
        break;

    // 鼠标释放事件
    case QEvent::MouseButtonRelease:
        {
            m_bDrag = false;
            m_bResize = false;
            m_bPressed = false;
            QWidget *pWidget = qobject_cast<QWidget *>(obj);
            pWidget->setCursor(Qt::ArrowCursor);
        }
        break;

    // 双击标题栏最大化、还原
    case QEvent::MouseButtonDblClick:
        {
            // 如果可以最大化的才做处理
//            if (m_bMaxable)
//            {
//                QMouseEvent *pMouseEvent = static_cast<QMouseEvent *>(event);
//                QWidget *pWidget = qobject_cast<QWidget *>(obj);

//                if (pMouseEvent->pos().y() <35)
//                {
//                    if (pWidget->windowState() & Qt::WindowMaximized)
//                    {
//                        pWidget->showNormal();
//                        setResizable(true);
//                    }
//                    else
//                    {
//                        pWidget->showMaximized();
//                        setResizable(false);
//                    }
//                }
//            }
        }

    default:
        break;
    }
    return QObject::eventFilter(obj, event);
}

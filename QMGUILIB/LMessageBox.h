/************************************************************************
* 文件名称：LMessageBox.h
* 编写人员：oLHHo
* 项目组织：C++/Qt项目组
* 创建日期：2017/10/10
* 功能描述：自定义QMessageBox消息框
* 备    注：
* 修改描述：
************************************************************************/
#ifndef LMESSAGEBOX_H
#define LMESSAGEBOX_H

#include "IconHelper.h"
#include <QWidget>
#include <QMouseEvent>
#include <QPoint>

class LCommon;

namespace Ui {
class LMessageBox;
}

class LMessageBox : public QWidget
{
    Q_OBJECT

public:
    explicit LMessageBox(QWidget *parent = 0);
    ~LMessageBox();

    /*
    * @author by lhh
    * @brief 单例模式
    * @param 无
    * @return 实例化对象
    */
    static LMessageBox* Instance();

    /*
    * @author by lhh
    * @brief 界面初始化
    * @param 无
    * @return void
    */
    void InitUI();

    /*
    * @author by lhh
    * @brief 控件信号的连接
    * @param 无
    * @return void
    */
    void SignalConnects();


public:
    /*
    * @author by lhh
    * @brief 设置消息内容及类别
    * @param strText 消息内容
    * @param type 消息类别
    * @return void
    */
    void setMsgType(const QString& strText, const int type);

private slots:
    void OnOKBtn();

    /*
    * @author by lhh
    * @brief 鼠标按下事件
    * @param 鼠标事件
    * @return void
    */
    void mousePressEvent(QMouseEvent *event);

    /*
    * @author by lhh
    * @brief 鼠标移动事件
    * @param 鼠标事件
    * @return void
    */
    void mouseMoveEvent(QMouseEvent *event);

    /*
    * @author by lhh
    * @brief 鼠标释放事件
    * @param 鼠标事件
    * @return void
    */
    void mouseReleaseEvent(QMouseEvent *);

private:
    QPoint move_point;  // 移动的距离
    QPoint move_pos;    // 移动到屏幕上的位置
    bool mouse_press;   // 鼠标按下


private:
    Ui::LMessageBox *ui;

    static LMessageBox* m_pLMessageBox;
};

#endif // LMESSAGEBOX_H

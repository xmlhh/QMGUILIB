/************************************************************************
*   文件名称：LDrawWgt.h
*   编写人员：LHH
*   创建日期：2016/02/01
*   功能描述：自定义窗口：去边框、实现窗口基本UI布局、开放公共接口
*   备    注：
*   修改描述：
*   团    队：C++/Qt项目组
************************************************************************/

#ifndef LDRAWWGT_H
#define LDRAWWGT_H

#include "qmguilib_global.h"
#include "LDrawFilterWgt.h"
#include "IconHelper.h"

#include <QObject>
#include <QtWidgets/QWidget>
#include <QPushButton>
#include <QLabel>


class QMGUILIBSHARED_EXPORT LDrawWgt : public QWidget
{
    Q_OBJECT

public:
    LDrawWgt(QWidget *parent = 0);
    ~LDrawWgt();

public:
    /************************************************************************
    *   外部公共接口——开始
    ************************************************************************/
    /**
    * @author by LHH
    * @brief 设置窗口标题，重写基类函数
    * @param 无
    * @return void
    */
    QMGUILIBSHARED_EXPORT void setWindowTitle(const QString& text);

    /**
    * @author by LHH
    * @brief 设置是否可以拖动
    * @param 无
    * @return void
    */
    QMGUILIBSHARED_EXPORT void setDragable(bool bDragable);

    /**
    * @author by LHH
    * @brief 设置是否可以缩放
    * @param 无
    * @return void
    */
    QMGUILIBSHARED_EXPORT void setResizable(bool bResizable);

    /**
    * @author by LHH
    * @brief 设置是否可以最大化
    * @param 无
    * @return void
    */
    QMGUILIBSHARED_EXPORT void setMaxable(bool bMaxable);

    /**
    * @author by LHH
    * @brief 设置是否显示最小化按钮
    * @param 无
    * @return void
    */
    QMGUILIBSHARED_EXPORT void setShowMinBtn(bool bMin);

    /**
    * @author by LHH
    * @brief 设置是否显示最大化按钮
    * @param 无
    * @return void
    */
    QMGUILIBSHARED_EXPORT void setShowMaxBtn(bool bMax);

    /**
    * @author by LHH
    * @brief 设置是否显示选项按钮
    * @param 无
    * @return void
    */
    QMGUILIBSHARED_EXPORT void setShowMoreOptions(bool bOpt);
    /************************************************************************
    *   外部公共接口——结束
    ************************************************************************/

private slots:
    /**
    * @author by LHH
    * @brief 最大化和还原按钮切换
    * @param 无
    * @return void
    */
    void OnMaxRestoreBtn();

    /**
    * @author by LHH
    * @brief 点击更多选项执行的操作（弹出对话框或下拉列表）
    * @param 无
    * @return void
    */
    void OnOptionsBtn();

public:
    // 中心窗口
    QWidget *m_pCenterWidget;

    // 标题栏窗口
    QWidget *m_pHeaderWidget;

    // 标题栏图标
    QLabel *m_pHeaderIcon;

    // 标题栏名称控件
    QLabel *m_pHeaderLabel;

    // 选项按钮
    QPushButton *m_pOptBtn;

    // 最小化按钮
    QPushButton *m_pMinBtn;

    // 最大化按钮
    QPushButton *m_pMaxBtn;

    // 关闭按钮控件
    QPushButton *m_pCloseBtn;

private:
    /**
    * @author by LHH
    * @brief 初始化界面
    * @param 无
    * @return void
    */
    void InitUI();

    /**
    * @author by LHH
    * @brief 设置基本布局
    * @param 无
    * @return void
    */
    void setUpDlgUi();

    // 主窗口
    QWidget *m_pBgWidget;

    // 指针事件类对象
    LDrawFilterWgt *m_pFilter;

    // 最大化/还原的标识
    bool m_bMaxFlag;
};

#endif // LDRAWWGT_H

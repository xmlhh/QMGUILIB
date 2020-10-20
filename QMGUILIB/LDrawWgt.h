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
#include "LCommon.h"

#include <QObject>
#include <QtWidgets/QWidget>

class QPushButton;
class QToolButton;
class QLabel;
class QPixmap;
class QSizePolicy;
class QButtonGroup;
class QMenu;
class QAction;
class QResizeEvent;
class QPaintEvent;
class QPainter;

class QMGUILIBSHARED_EXPORT LDrawWgt : public QWidget
{
    Q_OBJECT

public:
    LDrawWgt(QWidget *parent = 0);
    ~LDrawWgt();

    // 标题栏布局
    enum ETitleType {
        NORMAL = 0,
        SMALL,
        MEDIUM,
        LARGE,
        SHADOW
    };

    Q_ENUM(ETitleType)

public:
    /************************************************************************
    *   外部公共接口——开始
    ************************************************************************/
    /**
    * @author by LHH
    * @brief    设置是否隐藏标题栏图标
    * @param    无
    * @return   void
    */
    void setShowTitleIcon(bool bIcon);

    /**
    * @author by LHH
    * @brief    设置窗口标题，重写基类函数
    * @param    无
    * @return   void
    */
    void setWindowTitle(const QString &text);

    /**
    * @author by LHH
    * @brief    设置是否可以拖动
    * @param    无
    * @return   void
    */
    void setDragable(bool bDragable);

    /**
    * @author by LHH
    * @brief    设置是否可以缩放
    * @param    无
    * @return   void
    */
    void setResizable(bool bResizable);

    /**
    * @author by LHH
    * @brief    设置是否可以最大化
    * @param    无
    * @return   void
    */
    void setMaxable(bool bMaxable);

    /**
    * @author by LHH
    * @brief    设置是否显示最小化按钮
    * @param    无
    * @return   void
    */
    void setShowMinBtn(bool bMin);

    /**
    * @author by LHH
    * @brief    设置是否显示最大化按钮
    * @param    无
    * @return   void
    */
    void setShowMaxBtn(bool bMax);

    /**
    * @author by LHH
    * @brief    选项添加action
    * @param    无
    * @return   void
    */
    void addOptionAct(const QString &strText);

    /**
    * @author by LHH
    * @brief    设置是否显示选项按钮
    * @param    无
    * @return   void
    */
    void setShowMoreOptions(bool bOpt);

    /**
    * @author by LHH
    * @brief    初始化界面
    * @param    无
    * @return   void
    */
    void InitTitle(ETitleType eTitleType);

    /************************************************************************
    *   外部公共接口——结束
    ************************************************************************/


signals:
    void sig_action(bool);

private slots:
    /**
    * @author by LHH
    * @brief    最大化和还原按钮切换
    * @param    无
    * @return   void
    */
    void OnMaxRestoreBtn();

    /**
    * @author by LHH
    * @brief    点击更多选项执行的操作（弹出对话框或下拉列表）
    * @param    无
    * @return   void
    */
    void OnOptionsBtn();

    /**
    * @author by lhh
    * @brief    按钮组的槽，组内按钮互斥
    * @param    当前点击的按钮
    * @return   void
    */
    void OnGroupClickedBtn(QAbstractButton *cBtn);

    /**
    * @author by LHH
    * @brief    切换界面样式
    * @param    bool
    * @return   void
    */
    void OnSetStyleLightBlue(bool );

    void OnSetStyleSkyBlue(bool );
    void OnSetStyleDarkBlue(bool );

    void OnSetStyleGray(bool );

    void OnSetStyleBlack(bool );

    void OnSetStylePsBlack(bool );

    void OnSetStyleVsBlack(bool );

    void OnAction(bool flag);

public:
    // 阴影窗口
    QWidget *m_pShadowWidget;
    // 主窗口
    QWidget *m_pBgWidget;
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
    // 按钮组
    QButtonGroup *m_pToolGroupBtn;

    QMenu *m_pPopMenu;

    ETitleType m_eTitleType;

private:
    /**
    * @author by LHH
    * @brief    初始化界面
    * @param    无
    * @return   void
    */
    void InitTitle();

    /**
    * @author by LHH
    * @brief    设置标题栏布局
    * @param    无
    * @return   void
    */
    void setTitleLayout(ETitleType eTitleType);

    void setUpDlgUi();

    /**
    * @author by LHH
    * @brief    标题栏：小边标题栏+小按钮组+小菜单栏（invisible）
    * @return   void
    */
    void setUpDlgUi_1();

    /**
    * @author by LHH
    * @brief    标题栏：小边标题栏+小按钮组（上）+大按钮组(菜单)（下）
    * @return   void
    */
    void setUpDlgUi_2();

    /**
    * @author by LHH
    * @brief    标题栏：大标题栏（左）+ 小按钮组（右上）
    * @return   void
    */
    void setUpDlgUi_3();

    /**
    * @author by LHH
    * @brief    标题栏：大标题栏（左）+ 小按钮组（右上）+ 窗口阴影框
    * @return   void
    */
    void setUpDlgUi_4();

    /**
    * @author by LHH
    * @brief    菜单选项
    * @return   void
    */
    void initMenuOption();

    // 指针事件类对象
    LDrawFilterWgt *m_pFilter;
    // 按钮组互斥标识
    bool m_bFlagBtn;
    // 最大化/还原的标识
    bool m_bMaxFlag;

};

#endif // LDRAWWGT_H

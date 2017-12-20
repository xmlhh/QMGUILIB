#include "LDrawWgt.h"

#include <QPushButton>
#include <QToolButton>
#include <QLabel>
#include <QPixmap>
#include <QSizePolicy>
#include <QButtonGroup>
#include <QMenu>
#include <QAction>

#define BTN_MAX_SIZE 6

LDrawWgt::LDrawWgt(QWidget *parent)
    :QWidget(parent)
    , m_bFlagBtn(true)
    , m_bMaxFlag(false)
{
    InitUI();
}


LDrawWgt::~LDrawWgt()
{

}

/**
* @author by LHH
* @brief 初始化界面
* @param 无
* @return void
*/
void LDrawWgt::InitUI()
{
#if 0
    setUpDlgUi_1();
    IconHelper::Instance()->SetIcon(m_pHeaderIcon, QChar(0xf118), 12);
#else
    //setUpDlgUi_2();
    //IconHelper::Instance()->SetIcon(m_pHeaderIcon, QChar(0xf118), 12);
//#else
    setUpDlgUi_3();
#endif

    //补充Qt::Dialog属性，可以提升窗口拖动的效率
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    this->setWindowOpacity(0.95);
    m_pFilter = new LDrawFilterWgt(this);
    this->installEventFilter(m_pFilter);

    // 使用字库图标
    IconHelper::Instance()->SetIcon(m_pHeaderIcon, QChar(0xf118), 12);
    IconHelper::Instance()->SetIcon(m_pMinBtn, QChar(0xf068), 11);
    IconHelper::Instance()->SetIcon(m_pMaxBtn, QChar(0xf2d0), 11);
    IconHelper::Instance()->SetIcon(m_pCloseBtn, QChar(0xf00d), 11);
    IconHelper::Instance()->SetIcon(m_pOptBtn, QChar(0xf0ca), 12);
}


/**
* @author by LHH
* @brief 设置基本布局
* @param 无
* @return void
*/
void LDrawWgt::setUpDlgUi()
{
    // 新建主垂直布局
    QVBoxLayout *pBgLayout = new QVBoxLayout(this);
    pBgLayout->setSpacing(0);
    pBgLayout->setMargin(0);

    // 新建主窗口
    m_pBgWidget = new QWidget(this);
    m_pBgWidget->setObjectName("m_pBgWidget");
    pBgLayout->addWidget(m_pBgWidget);

    // 新建主窗口垂直布局
    QVBoxLayout *pMainVBoxLayout = new QVBoxLayout(m_pBgWidget);
    pMainVBoxLayout->setSpacing(0);
    pMainVBoxLayout->setMargin(0);

    // 新建标题栏窗口
    m_pHeaderWidget = new QWidget(m_pBgWidget);
    m_pHeaderWidget->setObjectName("m_pHeaderWidget");
    m_pHeaderWidget->setMinimumSize(QSize(0, 35));
    m_pHeaderWidget->setMaximumSize(QSize(16777215, 35));

    // 新建标题栏水平布局
    QHBoxLayout *pHeaderHBoxLayout = new QHBoxLayout(m_pHeaderWidget);
    pHeaderHBoxLayout->setSpacing(0);
    pHeaderHBoxLayout->setContentsMargins(15, 0, 0, 4);

    // 标题栏图标
    m_pHeaderIcon = new QLabel(m_pHeaderWidget);
    m_pHeaderIcon->setObjectName("m_pHeaderIcon");
    m_pHeaderIcon->setMinimumSize(QSize(30, 30));

    // 新建标题栏名称控件
    m_pHeaderLabel = new QLabel(m_pHeaderWidget);
    m_pHeaderLabel->setObjectName("m_pHeaderLabel");
    m_pHeaderLabel->setMinimumSize(QSize(145, 0));

    // 将标题栏名称控件添加到标题栏水平布局中
    pHeaderHBoxLayout->addWidget(m_pHeaderIcon);
    pHeaderHBoxLayout->addWidget(m_pHeaderLabel);
    pHeaderHBoxLayout->addStretch();

    // 新建更多选项
    m_pOptBtn = new QPushButton(m_pHeaderWidget);
    m_pOptBtn->setObjectName("m_pOptBtn");
    m_pOptBtn->setMinimumSize(QSize(38, 30));
    m_pOptBtn->setMaximumSize(QSize(38, 30));
    m_pOptBtn->setText("");
    m_pOptBtn->setFlat(true);
    m_pOptBtn->setToolTip("选项");
    m_pOptBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_pOptBtn, SIGNAL(clicked()), this, SLOT(OnOptionsBtn()));

    // 新建最小化按钮
    m_pMinBtn = new QPushButton(m_pHeaderWidget);
    m_pMinBtn->setObjectName("m_pMinBtn");
    m_pMinBtn->setMinimumSize(QSize(38, 30));
    m_pMinBtn->setMaximumSize(QSize(38, 30));
    m_pMinBtn->setText("");
    m_pMinBtn->setFlat(true);
    m_pMinBtn->setToolTip("最小化");
    m_pMinBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_pMinBtn, SIGNAL(clicked()), this, SLOT(showMinimized()));

    // 新建最大化按钮
    m_pMaxBtn = new QPushButton(m_pHeaderWidget);
    m_pMaxBtn->setObjectName("m_pMaxBtn");
    m_pMaxBtn->setMinimumSize(QSize(38, 30));
    m_pMaxBtn->setMaximumSize(QSize(38, 30));
    m_pMaxBtn->setText("");
    m_pMaxBtn->setFlat(true);
    m_pMaxBtn->setToolTip("最大化");
    m_pMaxBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_pMaxBtn, SIGNAL(clicked()), this, SLOT(OnMaxRestoreBtn()));

    // 新建标题栏关闭按钮控件
    m_pCloseBtn = new QPushButton(m_pHeaderWidget);
    m_pCloseBtn->setObjectName("m_pCloseBtn");
    m_pCloseBtn->setMinimumSize(QSize(38, 30));
    m_pCloseBtn->setMaximumSize(QSize(38, 30));
    m_pCloseBtn->setText("");
    m_pCloseBtn->setFlat(true);
    m_pCloseBtn->setToolTip("关闭");
    m_pCloseBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_pCloseBtn, SIGNAL(clicked()), this, SLOT(close()));

    // 将关闭按钮控件添加到标题栏水平布局中
    pHeaderHBoxLayout->addWidget(m_pOptBtn);
    pHeaderHBoxLayout->addWidget(m_pMinBtn);
    pHeaderHBoxLayout->addWidget(m_pMaxBtn);
    pHeaderHBoxLayout->addWidget(m_pCloseBtn);

    // 将标题栏窗口添加到主垂直布局中
    pMainVBoxLayout->addWidget(m_pHeaderWidget);

    // 新建中心窗口
    m_pCenterWidget = new QWidget;

    // 将中心窗口添加到主垂直布局中
    pMainVBoxLayout->addWidget(m_pCenterWidget);
}

/**
* @author by LHH
* @brief 标题栏：小边标题栏+小按钮组+小菜单栏（invisible）
* @return void
*/
void LDrawWgt::setUpDlgUi_1()
{
    // 新建主垂直布局
    QVBoxLayout *pBgLayout = new QVBoxLayout(this);
    pBgLayout->setSpacing(0);
    pBgLayout->setMargin(0);

    // 新建主窗口
    m_pBgWidget = new QWidget(this);
    m_pBgWidget->setObjectName("m_pBgWidget");
    pBgLayout->addWidget(m_pBgWidget);

    // 新建主窗口垂直布局
    QVBoxLayout *pMainVBoxLayout = new QVBoxLayout(m_pBgWidget);
    pMainVBoxLayout->setSpacing(0);
    pMainVBoxLayout->setMargin(0);

    // 新建标题栏窗口
    m_pHeaderWidget = new QWidget(m_pBgWidget);
    m_pHeaderWidget->setObjectName("m_pHeaderWidget");
    m_pHeaderWidget->setMinimumSize(QSize(0, 35));
    m_pHeaderWidget->setMaximumSize(QSize(16777215, 35));

    // 新建标题栏水平布局
    QHBoxLayout *pHeaderHBoxLayout = new QHBoxLayout(m_pHeaderWidget);
    pHeaderHBoxLayout->setSpacing(0);
    pHeaderHBoxLayout->setContentsMargins(15, 0, 0, 4);

    // 标题栏图标
    m_pHeaderIcon = new QLabel(m_pHeaderWidget);
    m_pHeaderIcon->setObjectName("m_pHeaderIcon");
    m_pHeaderIcon->setMinimumSize(QSize(30, 35));

    // 新建标题栏名称控件
    m_pHeaderLabel = new QLabel(m_pHeaderWidget);
    m_pHeaderLabel->setObjectName("m_pHeaderLabel");
    m_pHeaderLabel->setMinimumSize(QSize(145, 0));

    // 将标题栏名称控件添加到标题栏水平布局中
    pHeaderHBoxLayout->addWidget(m_pHeaderIcon);
    pHeaderHBoxLayout->addWidget(m_pHeaderLabel);
    pHeaderHBoxLayout->addStretch();

    // 新建更多选项
    m_pOptBtn = new QPushButton(m_pHeaderWidget);
    m_pOptBtn->setObjectName("m_pOptBtn");
    m_pOptBtn->setMinimumSize(QSize(38, 35));
    m_pOptBtn->setMaximumSize(QSize(38, 35));
    m_pOptBtn->setText("");
    m_pOptBtn->setFlat(true);
    m_pOptBtn->setToolTip("选项");
    m_pOptBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_pOptBtn, SIGNAL(clicked()), this, SLOT(OnOptionsBtn()));

    // 新建最小化按钮
    m_pMinBtn = new QPushButton(m_pHeaderWidget);
    m_pMinBtn->setObjectName("m_pMinBtn");
    m_pMinBtn->setMinimumSize(QSize(38, 35));
    m_pMinBtn->setMaximumSize(QSize(38, 35));
    m_pMinBtn->setText("");
    m_pMinBtn->setFlat(true);
    m_pMinBtn->setToolTip("最小化");
    m_pMinBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_pMinBtn, SIGNAL(clicked()), this, SLOT(showMinimized()));

    // 新建最大化按钮
    m_pMaxBtn = new QPushButton(m_pHeaderWidget);
    m_pMaxBtn->setObjectName("m_pMaxBtn");
    m_pMaxBtn->setMinimumSize(QSize(38, 35));
    m_pMaxBtn->setMaximumSize(QSize(38, 35));
    m_pMaxBtn->setText("");
    m_pMaxBtn->setFlat(true);
    m_pMaxBtn->setToolTip("最大化");
    m_pMaxBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_pMaxBtn, SIGNAL(clicked()), this, SLOT(OnMaxRestoreBtn()));

    // 新建标题栏关闭按钮控件
    m_pCloseBtn = new QPushButton(m_pHeaderWidget);
    m_pCloseBtn->setObjectName("m_pCloseBtn");
    m_pCloseBtn->setMinimumSize(QSize(38, 35));
    m_pCloseBtn->setMaximumSize(QSize(38, 35));
    m_pCloseBtn->setText("");
    m_pCloseBtn->setFlat(true);
    m_pCloseBtn->setToolTip("关闭");
    m_pCloseBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_pCloseBtn, SIGNAL(clicked()), this, SLOT(close()));

    // 将关闭按钮控件添加到标题栏水平布局中
    pHeaderHBoxLayout->addWidget(m_pOptBtn);
    pHeaderHBoxLayout->addWidget(m_pMinBtn);
    pHeaderHBoxLayout->addWidget(m_pMaxBtn);
    pHeaderHBoxLayout->addWidget(m_pCloseBtn);

    // 将标题栏窗口添加到主垂直布局中
    pMainVBoxLayout->addWidget(m_pHeaderWidget);

    // 新建中心窗口
    m_pCenterWidget = new QWidget;

    // 将中心窗口添加到主垂直布局中
    pMainVBoxLayout->addWidget(m_pCenterWidget);
}


/**
* @author by LHH
* @brief 标题栏：小边标题栏+小按钮组（上）+大按钮组(菜单)（下）
* @return void
*/
void LDrawWgt::setUpDlgUi_2()
{
    // 新建主垂直布局
    QVBoxLayout *pBgLayout = new QVBoxLayout(this);
    pBgLayout->setSpacing(0);
    pBgLayout->setMargin(0);

    // 新建主窗口
    m_pBgWidget = new QWidget(this);
    m_pBgWidget->setObjectName("m_pBgWidget");
    pBgLayout->addWidget(m_pBgWidget);

    // 新建主窗口垂直布局
    QVBoxLayout *pMainVBoxLayout = new QVBoxLayout(m_pBgWidget);
    pMainVBoxLayout->setSpacing(0);
    pMainVBoxLayout->setMargin(0);

    // 新建标题栏窗口
    m_pHeaderWidget = new QWidget(m_pBgWidget);
    m_pHeaderWidget->setObjectName("m_pHeaderWidget");
    m_pHeaderWidget->setMinimumSize(QSize(0, 120));
    m_pHeaderWidget->setMaximumSize(QSize(16777215, 120));

    // 新建标题栏垂直布局
    QVBoxLayout *pHeaderVBoxLayout = new QVBoxLayout(m_pHeaderWidget);
    pHeaderVBoxLayout->setSpacing(0);
    pHeaderVBoxLayout->setContentsMargins(15, 0, 0, 0);

    // 新建标题栏+配置按钮行
    QWidget *pHeaderTitleWgt = new QWidget(m_pHeaderWidget);
    pHeaderTitleWgt->setMinimumSize(QSize(0, 35));
    pHeaderTitleWgt->setMaximumSize(QSize(16777215, 35));

    QHBoxLayout *pHeaderTitleHBoxLayout = new QHBoxLayout(pHeaderTitleWgt);
    pHeaderTitleHBoxLayout->setSpacing(0);
    pHeaderTitleHBoxLayout->setContentsMargins(0, 0, 0, 0);


    // 标题栏图标
    m_pHeaderIcon = new QLabel(pHeaderTitleWgt);
    m_pHeaderIcon->setObjectName("m_pHeaderIcon");
    m_pHeaderIcon->setMinimumSize(QSize(30, 35));

    // 新建标题栏名称控件
    m_pHeaderLabel = new QLabel(pHeaderTitleWgt);
    m_pHeaderLabel->setObjectName("m_pHeaderLabel");
    m_pHeaderLabel->setMinimumSize(QSize(145, 0));

    // 将标题栏名称控件添加到标题栏水平布局中
    pHeaderTitleHBoxLayout->addWidget(m_pHeaderIcon);
    pHeaderTitleHBoxLayout->addWidget(m_pHeaderLabel);
    pHeaderTitleHBoxLayout->addStretch();
    pHeaderTitleHBoxLayout->setContentsMargins(5, 0, 0, 0);

    // 新建选项
    m_pOptBtn = new QPushButton(pHeaderTitleWgt);
    m_pOptBtn->setObjectName("m_pOptBtn");
    m_pOptBtn->setMinimumSize(QSize(38, 35));
    m_pOptBtn->setMaximumSize(QSize(38, 35));
    m_pOptBtn->setText("");
    m_pOptBtn->setFlat(true);
    m_pOptBtn->setToolTip("选项");
    m_pOptBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_pOptBtn, SIGNAL(clicked()), this, SLOT(OnOptionsBtn()));

    // 新建最小化按钮
    m_pMinBtn = new QPushButton(pHeaderTitleWgt);
    m_pMinBtn->setObjectName("m_pMinBtn");
    m_pMinBtn->setMinimumSize(QSize(38, 35));
    m_pMinBtn->setMaximumSize(QSize(38, 35));
    m_pMinBtn->setText("");
    m_pMinBtn->setFlat(true);
    m_pMinBtn->setToolTip("最小化");
    m_pMinBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_pMinBtn, SIGNAL(clicked()), this, SLOT(showMinimized()));

    // 新建最大化按钮
    m_pMaxBtn = new QPushButton(pHeaderTitleWgt);
    m_pMaxBtn->setObjectName("m_pMaxBtn");
    m_pMaxBtn->setMinimumSize(QSize(38, 35));
    m_pMaxBtn->setMaximumSize(QSize(38, 35));
    m_pMaxBtn->setText("");
    m_pMaxBtn->setFlat(true);
    m_pMaxBtn->setToolTip("最大化");
    m_pMaxBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_pMaxBtn, SIGNAL(clicked()), this, SLOT(OnMaxRestoreBtn()));

    // 新建标题栏关闭按钮控件
    m_pCloseBtn = new QPushButton(pHeaderTitleWgt);
    m_pCloseBtn->setObjectName("m_pCloseBtn");
    m_pCloseBtn->setMinimumSize(QSize(38, 35));
    m_pCloseBtn->setMaximumSize(QSize(38, 35));
    m_pCloseBtn->setText("");
    m_pCloseBtn->setFlat(true);
    m_pCloseBtn->setToolTip("关闭");
    m_pCloseBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_pCloseBtn, SIGNAL(clicked()), this, SLOT(close()));

    // 将关闭按钮控件添加到标题栏水平布局中
    pHeaderTitleHBoxLayout->addWidget(m_pOptBtn);
    pHeaderTitleHBoxLayout->addWidget(m_pMinBtn);
    pHeaderTitleHBoxLayout->addWidget(m_pMaxBtn);
    pHeaderTitleHBoxLayout->addWidget(m_pCloseBtn);

    // 新建工具按钮组(Big)
    QWidget *pGroupMenuBtnWgt = new QWidget(m_pHeaderWidget);
    QHBoxLayout *pGroupMenuBtnHBoxLayout = new QHBoxLayout(pGroupMenuBtnWgt);
    pGroupMenuBtnHBoxLayout->setSpacing(2);
    pGroupMenuBtnHBoxLayout->setContentsMargins(5, 0, 0, 0);

    // 创建按钮组
    QList<QPushButton*> btnLst;
    for (int iIndex = 0; iIndex < BTN_MAX_SIZE; ++iIndex)
    {
        QPushButton *pageBtn = new QPushButton(pGroupMenuBtnWgt);
        pageBtn->setText(QString("Btn_%1").arg(iIndex+1));
        pageBtn->setMinimumSize(QSize(100, 80));
        pageBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

        btnLst.append(pageBtn);
    }

    // 按钮组
    m_pToolGroupBtn = new QButtonGroup;
    QObject::connect(m_pToolGroupBtn, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(OnGroupClickedBtn(QAbstractButton*)));
    for (int iIndex = 0; iIndex < BTN_MAX_SIZE; ++iIndex)
    {
        m_pToolGroupBtn->addButton(btnLst[iIndex], iIndex + 1);
    }

    // 将按钮组添加到水平布局
    for (int iIndex = 0; iIndex < BTN_MAX_SIZE; ++iIndex)
    {
        pGroupMenuBtnHBoxLayout->addWidget(btnLst[iIndex]);
    }
    pGroupMenuBtnHBoxLayout->addStretch();

    pHeaderVBoxLayout->addWidget(pHeaderTitleWgt);
    pHeaderVBoxLayout->addWidget(pGroupMenuBtnWgt);

    // 将标题栏窗口添加到主垂直布局中
    pMainVBoxLayout->addWidget(m_pHeaderWidget);

    // 新建中心窗口
    m_pCenterWidget = new QWidget;

    // 将中心窗口添加到主垂直布局中
    pMainVBoxLayout->addWidget(m_pCenterWidget);
}


/**
* @author by LHH
* @brief 标题栏：大标题栏（左）+ 小按钮组（右上）
* @return void
*/
void LDrawWgt::setUpDlgUi_3()
{
    // 新建主垂直布局
    QVBoxLayout *pBgLayout = new QVBoxLayout(this);
    pBgLayout->setSpacing(0);
    pBgLayout->setMargin(0);

    // 新建主窗口
    m_pBgWidget = new QWidget(this);
    m_pBgWidget->setObjectName("m_pBgWidget");
    pBgLayout->addWidget(m_pBgWidget);

    // 新建主窗口垂直布局
    QVBoxLayout *pMainVBoxLayout = new QVBoxLayout(m_pBgWidget);
    pMainVBoxLayout->setSpacing(0);
    pMainVBoxLayout->setMargin(0);

    // 新建标题栏窗口
    m_pHeaderWidget = new QWidget(m_pBgWidget);
    m_pHeaderWidget->setObjectName("m_pHeaderWidget");
    m_pHeaderWidget->setMinimumSize(QSize(0, 100));
    m_pHeaderWidget->setMaximumSize(QSize(16777215, 100));

    // 新建标题栏垂直布局
    QVBoxLayout *pHeaderVBoxLayout = new QVBoxLayout(m_pHeaderWidget);
    pHeaderVBoxLayout->setSpacing(0);
    pHeaderVBoxLayout->setContentsMargins(15, 0, 0, 0);

    // 新建标题栏+配置按钮行
    QWidget *pHeaderGroupBtnWgt = new QWidget(m_pHeaderWidget);
    pHeaderGroupBtnWgt->setMinimumSize(QSize(0, 35));
    pHeaderGroupBtnWgt->setMaximumSize(QSize(16777215, 35));

    QHBoxLayout *pHeaderGroupBtnHBoxLayout = new QHBoxLayout(pHeaderGroupBtnWgt);
    pHeaderGroupBtnHBoxLayout->setSpacing(0);
    pHeaderGroupBtnHBoxLayout->setContentsMargins(0, 0, 0, 0);

    // 新建选项
    m_pOptBtn = new QPushButton(pHeaderGroupBtnWgt);
    m_pOptBtn->setObjectName("m_pOptBtn");
    m_pOptBtn->setMinimumSize(QSize(38, 35));
    m_pOptBtn->setMaximumSize(QSize(38, 35));
    m_pOptBtn->setText("");
    m_pOptBtn->setFlat(true);
    m_pOptBtn->setToolTip("选项");
    m_pOptBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_pOptBtn, SIGNAL(clicked()), this, SLOT(OnOptionsBtn()));

    // 新建最小化按钮
    m_pMinBtn = new QPushButton(pHeaderGroupBtnWgt);
    m_pMinBtn->setObjectName("m_pMinBtn");
    m_pMinBtn->setMinimumSize(QSize(38, 35));
    m_pMinBtn->setMaximumSize(QSize(38, 35));
    m_pMinBtn->setText("");
    m_pMinBtn->setFlat(true);
    m_pMinBtn->setToolTip("最小化");
    m_pMinBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_pMinBtn, SIGNAL(clicked()), this, SLOT(showMinimized()));

    // 新建最大化按钮
    m_pMaxBtn = new QPushButton(pHeaderGroupBtnWgt);
    m_pMaxBtn->setObjectName("m_pMaxBtn");
    m_pMaxBtn->setMinimumSize(QSize(38, 35));
    m_pMaxBtn->setMaximumSize(QSize(38, 35));
    m_pMaxBtn->setText("");
    m_pMaxBtn->setFlat(true);
    m_pMaxBtn->setToolTip("最大化");
    m_pMaxBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_pMaxBtn, SIGNAL(clicked()), this, SLOT(OnMaxRestoreBtn()));

    // 新建标题栏关闭按钮控件
    m_pCloseBtn = new QPushButton(pHeaderGroupBtnWgt);
    m_pCloseBtn->setObjectName("m_pCloseBtn");
    m_pCloseBtn->setMinimumSize(QSize(38, 35));
    m_pCloseBtn->setMaximumSize(QSize(38, 35));
    m_pCloseBtn->setText("");
    m_pCloseBtn->setFlat(true);
    m_pCloseBtn->setToolTip("关闭");
    m_pCloseBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_pCloseBtn, SIGNAL(clicked()), this, SLOT(close()));

    // 将关闭按钮控件添加到标题栏水平布局中
    pHeaderGroupBtnHBoxLayout->addStretch();
    pHeaderGroupBtnHBoxLayout->addWidget(m_pOptBtn);
    pHeaderGroupBtnHBoxLayout->addWidget(m_pMinBtn);
    pHeaderGroupBtnHBoxLayout->addWidget(m_pMaxBtn);
    pHeaderGroupBtnHBoxLayout->addWidget(m_pCloseBtn);

    // 新建工具按钮组(Big)
    QWidget *pHeaderTitleWgt = new QWidget(m_pHeaderWidget);
    QHBoxLayout *pHeaderTitleHBoxLayout = new QHBoxLayout(pHeaderTitleWgt);
    pHeaderTitleHBoxLayout->setSpacing(2);
    pHeaderTitleHBoxLayout->setContentsMargins(20, 0, 0, 0);

    // 标题栏图标
    m_pHeaderIcon = new QLabel(pHeaderTitleWgt);
    m_pHeaderIcon->setObjectName("m_pHeaderIcon");
    m_pHeaderIcon->setMinimumSize(QSize(67, 48));
    m_pHeaderIcon->setMaximumSize(QSize(67, 48));
    m_pHeaderIcon->setPixmap(QPixmap(":/Data/Image/Icon.png").scaled(m_pHeaderIcon->size(), Qt::IgnoreAspectRatio));

    // 新建标题栏名称控件
    m_pHeaderLabel = new QLabel(pHeaderTitleWgt);
    m_pHeaderLabel->setObjectName("m_pHeaderLabel");
    m_pHeaderLabel->setMinimumSize(QSize(145, 0));

    // 将标题栏名称控件添加到标题栏水平布局中
    pHeaderTitleHBoxLayout->addWidget(m_pHeaderIcon);
    pHeaderTitleHBoxLayout->addWidget(m_pHeaderLabel);
    pHeaderTitleHBoxLayout->addStretch();

    pHeaderVBoxLayout->addWidget(pHeaderGroupBtnWgt);
    pHeaderVBoxLayout->addWidget(pHeaderTitleWgt);

    // 将标题栏窗口添加到主垂直布局中
    pMainVBoxLayout->addWidget(m_pHeaderWidget);

    // 新建中心窗口
    m_pCenterWidget = new QWidget;

    // 将中心窗口添加到主垂直布局中
    pMainVBoxLayout->addWidget(m_pCenterWidget);
}

// 设置窗口名称
void LDrawWgt::setWindowTitle(const QString& text)
{
    m_pHeaderLabel->setText(text);
}

// 设置可拖动
void LDrawWgt::setDragable(bool bDragable)
{
    m_pFilter->setDragable(bDragable);
}

// 设置可改变大小
void LDrawWgt::setResizable(bool bResizable)
{
    m_pFilter->setResizable(bResizable);
    setAttribute(Qt::WA_Hover);
}

// 设置可最大化
void LDrawWgt::setMaxable(bool bMaxable)
{
    m_pFilter->setMaxable(bMaxable);
}

// 是否显示最小化按钮
void LDrawWgt::setShowMinBtn(bool bMin)
{
    m_pMinBtn->setHidden(!bMin);
}

// 是否显示最大化按钮
void LDrawWgt::setShowMaxBtn(bool bMax)
{
    m_pMaxBtn->setHidden(!bMax);
}

// 是否显示选项按钮
void LDrawWgt::setShowMoreOptions(bool bOpt)
{
    m_pOptBtn->setHidden(!bOpt);
}


/**
* @author by LHH
* @brief 最大化和还原按钮切换
* @param 无
* @return void
*/
void LDrawWgt::OnMaxRestoreBtn()
{
    if (m_bMaxFlag)
    {
        showNormal();
        m_pFilter->setDragable(true);
        m_pMaxBtn->setToolTip("最大化");
        IconHelper::Instance()->SetIcon(m_pMaxBtn, QChar(0xf2d0), 11);
    }
    else
    {
        showMaximized();
        m_pFilter->setDragable(false);
        m_pMaxBtn->setToolTip("还原");
        IconHelper::Instance()->SetIcon(m_pMaxBtn, QChar(0xf2d2), 11);
    }

    m_bMaxFlag = !m_bMaxFlag;
}


/**
* @author by LHH
* @brief 点击更多选项执行的操作（弹出对话框或下拉列表）
* @param no
* @return void
*/
void LDrawWgt::OnOptionsBtn()
{
    QMenu *popMenu = new QMenu(this);

    QAction *act_1 = new QAction("浅蓝色(平面)", this);
    QAction *act_2 = new QAction("天蓝色(凸面)", this);
    QAction *act_3 = new QAction("灰色", this);
    QAction *act_4 = new QAction("黑色", this);
    QAction *act_5 = new QAction("PS黑色", this);
    QAction *act_6 = new QAction("VS黑色", this);

    QObject::connect(act_1, SIGNAL(triggered(bool)), this, SLOT(OnSetStyleLightBlue(bool)));
    QObject::connect(act_2, SIGNAL(triggered(bool)), this, SLOT(OnSetStyleSkyBlue(bool)));
    QObject::connect(act_3, SIGNAL(triggered(bool)), this, SLOT(OnSetStyleGray(bool)));
    QObject::connect(act_4, SIGNAL(triggered(bool)), this, SLOT(OnSetStyleBlack(bool)));
    QObject::connect(act_5, SIGNAL(triggered(bool)), this, SLOT(OnSetStylePsBlack(bool)));
    QObject::connect(act_6, SIGNAL(triggered(bool)), this, SLOT(OnSetStyleVsBlack(bool)));

    popMenu->addAction(act_1);
    popMenu->addAction(act_2);
    popMenu->addAction(act_3);
    popMenu->addAction(act_4);
    popMenu->addAction(act_5);
    popMenu->addAction(act_6);

    m_pOptBtn->setMenu(popMenu);

}


/*
* @author by lhh
* @brief 按钮组的槽，组内按钮互斥
* @param 当前点击的按钮
* @return void
*/
void LDrawWgt::OnGroupClickedBtn(QAbstractButton* cBtn)
{
    if  (m_bFlagBtn)
    {
        cBtn->setChecked(m_bFlagBtn);
    }
}

void LDrawWgt::OnSetStyleLightBlue(bool)
{
    // 浅蓝色风格(平面)
    LCommon::SetStyle("blue_new");

}

void LDrawWgt::OnSetStyleSkyBlue(bool)
{
    // 天蓝色风格(凸面)
    LCommon::SetStyle("blue_2");
}

void LDrawWgt::OnSetStyleGray(bool)
{
    // 灰色风格
    LCommon::SetStyle("gray");

}

void LDrawWgt::OnSetStyleBlack(bool)
{
    // 黑色风格
    LCommon::SetStyle("black");
}


void LDrawWgt::OnSetStylePsBlack(bool)
{
    // 天蓝色风格(平面)
    LCommon::SetStyle("navy");
}

void LDrawWgt::OnSetStyleVsBlack(bool)
{
    // 天蓝色风格(平面)
    LCommon::SetStyle("navy");
}


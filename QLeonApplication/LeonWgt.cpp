#include "LeonWgt.h"
#include "ui_LeonWgt.h"
#include "../QMGUILIB/LCommon.h"

#define WIN_WIDTH 1000
#define WIN_HEIGHT 700

LeonWgt::LeonWgt(QWidget *parent) :
    LDrawWgt(parent),
    ui(new Ui::LeonWgt)
{
    InitUI();
}

LeonWgt::~LeonWgt()
{
    delete ui;
}


/**
* @author by LHH
* @brief 初始化界面
* @param 无
* @return void
*/
void LeonWgt::InitUI()
{
    //ui->setupUi(this);
    ui->setupUi(m_pCenterWidget);

    setWindowTitle("共享库测试界面");
    resize(WIN_WIDTH, WIN_HEIGHT);

    // 可拖拽
    setDragable(true);
    // 可最大化
    setMaxable(true);
    // 可缩放
    setResizable(true);

    // 显示选项按钮
    setShowMoreOptions(true);
    // 显示最小化按钮
    setShowMinBtn(true);
    // 显示最大化按钮
    setShowMaxBtn(true);

    SignalConnects();
}



/*
* @author by lhh
* @brief 控件的信号连接
* @param 无
* @return void
*/
void LeonWgt::SignalConnects()
{
    connect(ui->m_pInfomationBtn, SIGNAL(clicked()), this, SLOT(onInfomationBtn()));
    connect(ui->m_pQuestionBtn, SIGNAL(clicked()), this, SLOT(onQuestionBtn()));
    connect(ui->m_pWarningBtn, SIGNAL(clicked()), this, SLOT(onWarningBtn()));
    connect(ui->m_pErrorBtn, SIGNAL(clicked()), this, SLOT(onErrorBtn()));
}

void LeonWgt::onInfomationBtn()
{
    LCommon::ShowMessageBoxInfo("消息已发送完成！");

}

void LeonWgt::onQuestionBtn()
{
    LCommon::ShowMessageBoxQuesion("亲，你今天捡肥皂了吗？");
}

void LeonWgt::onWarningBtn()
{
    LCommon::ShowMessageBoxWarning("变量Leonm没有被使用！");
}

void LeonWgt::onErrorBtn()
{
    LCommon::ShowMessageBoxError("空指针异常！");
}

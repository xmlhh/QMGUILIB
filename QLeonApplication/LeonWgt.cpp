#include "LeonWgt.h"
#include "ui_LeonWgt.h"

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
}

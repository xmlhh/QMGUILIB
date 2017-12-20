#include "LMessageBox.h"
#include "ui_LMessageBox.h"
#include "LCommon.h"

#define WIN_WIDTH 300
#define WIN_HIEGHT 130

LMessageBox* LMessageBox::m_pLMessageBox = NULL;

LMessageBox::LMessageBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LMessageBox)
{

    InitUI();

}

LMessageBox::~LMessageBox()
{
    delete ui;
}


/*
* @author by lhh
* @brief 单例模式
* @param 无
* @return 实例化对象
*/
LMessageBox *LMessageBox::Instance()
{
    if (NULL == m_pLMessageBox)
    {
        m_pLMessageBox = new LMessageBox;
    }

    return m_pLMessageBox;
}


/*
* @author by lhh
* @brief 界面初始化
* @param 无
* @return void
*/
void LMessageBox::InitUI()
{
    ui->setupUi(this);
    resize(WIN_WIDTH, WIN_HIEGHT);

    setWindowOpacity(0.95);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint );
    // 模态对话框，阻塞父窗口
    setWindowModality(Qt::ApplicationModal);
#if 1// "非单例模式"
    // 窗体关闭时自动释放内存
    setAttribute(Qt::WA_DeleteOnClose);
#endif

    //设置图形字体
    IconHelper::Instance()->SetIcon(ui->m_pTitleIconLbl, QChar(0xf118), 12);
    IconHelper::Instance()->SetIcon(ui->m_pCloseBtn, QChar(0xf00d), 10);

    // 窗体居中显示
    LCommon::FormInCenter(this);

    SignalConnects();
}


/*
* @author by lhh
* @brief 控件信号的连接
* @param 无
* @return void
*/
void LMessageBox::SignalConnects()
{
    connect(ui->m_pCloseBtn, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->m_pOKBtn, SIGNAL(clicked()), this, SLOT(OnOKBtn()));
    connect(ui->m_pCancelBtn, SIGNAL(clicked()), this, SLOT(close()));
}


/*
* @author by lhh
* @brief 设置消息内容及类别
* @param strText 消息内容
* @param type 消息类别
* @return void
*/
void LMessageBox::setMsgType(const QString &strText, const int type)
{
    ui->m_pMsgTextLbl->setText(strText);

    switch(type)
    {
        case 0:
            ui->m_pTitleTextLbl->setText("提示");
            ui->m_pMsgIconLbl->setStyleSheet("border-image:url(:/Data/Image/info.png)");
            ui->m_pCancelBtn->setVisible(false);
            break;

        case 1:
            ui->m_pTitleTextLbl->setText("询问");
            ui->m_pMsgIconLbl->setStyleSheet("border-image:url(:/Data/Image/question.png)");
            ui->m_pCancelBtn->setVisible(true);
            break;

        case 2:
            ui->m_pTitleTextLbl->setText("警告");
            ui->m_pMsgIconLbl->setStyleSheet("border-image:url(:/Data/Image/error.png)");
            ui->m_pCancelBtn->setVisible(false);
            break;

        case 3:
            ui->m_pTitleTextLbl->setText("错误");
            ui->m_pMsgIconLbl->setStyleSheet("border-image:url(:/Data/Image/error.png)");
            ui->m_pCancelBtn->setVisible(false);
            break;

        default:
            break;
    }
}

void LMessageBox::OnOKBtn()
{
    this->close();
}


/*
* @author by lhh
* @brief 鼠标按下事件
* @param 鼠标事件
* @return void
*/
void LMessageBox::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        mouse_press = true;
        move_point = event->pos();
    }

    return QWidget::mousePressEvent(event);
}

/*
* @author by lhh
* @brief 鼠标移动事件
* @param 鼠标事件
* @return void
*/
void LMessageBox::mouseMoveEvent(QMouseEvent *event)
{
    if(mouse_press && (event->buttons() && Qt::LeftButton))
    {
        //只有点击到头部才能拖动
        //if (event->pos().y() < 30)
        //{
            move_pos = event->globalPos();
            this->move(move_pos - move_point);
            event->accept();
        //}
    }

    return QWidget::mouseMoveEvent(event);
}

/*
* @author by lhh
* @brief 鼠标释放事件
* @param 鼠标事件
* @return void
*/
void LMessageBox::mouseReleaseEvent(QMouseEvent *)
{
    mouse_press = false;
}

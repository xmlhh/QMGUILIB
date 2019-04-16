#ifndef LEONWGT_H
#define LEONWGT_H

#include <QWidget>
#include "../QMGUILIB/LDrawWgt.h"

namespace Ui {
class LeonWgt;
}

class LeonWgt : public LDrawWgt
{
    Q_OBJECT

public:
    explicit LeonWgt(QWidget *parent = 0);
    ~LeonWgt();

    /**
    * @author by LHH
    * @brief 初始化界面
    * @param 无
    * @return void
    */
    void InitUI();

    /*
    * @author by lhh
    * @brief 控件的信号连接
    * @param 无
    * @return void
    */
    void SignalConnects();

private slots:
    void onInfomationBtn();

    void onQuestionBtn();

    void onWarningBtn();

    void onErrorBtn();

private:
    Ui::LeonWgt *ui;
};

#endif // LEONWGT_H

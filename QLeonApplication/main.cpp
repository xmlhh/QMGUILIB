#include "LeonWgt.h"
#include "../QMGUILIB/LCommon.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LeonWgt w;

    // 初始界面样式
    LCommon::SetStyle("blue_1");
    // 中文翻译
    LCommon::SetChinese("qt_zh_CN");

    w.show();

    return a.exec();
}

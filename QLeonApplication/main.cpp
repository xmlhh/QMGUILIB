#include "LeonWgt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LeonWgt w;

    QFile file(":/Data/Css/blue_1.css");
    file.open(QFile::ReadOnly);
    QString qss = QLatin1String(file.readAll());
    qApp->setStyleSheet(qss);
    qApp->setPalette(QPalette(QColor("#F0F0F0")));

    QTranslator *translator = new QTranslator(qApp);
    translator->load("qt_zh_CN.qm");
    qApp->installTranslator(translator);

    w.show();

    return a.exec();
}

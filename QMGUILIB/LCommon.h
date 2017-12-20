#ifndef LCOMMON_H
#define LCOMMON_H

#include <QtCore>
#include <QtGui>
#include <QDesktopWidget>

#include "LMessageBox.h"

class LCommon: public QObject
{
public:
    //设置为开机启动
    static void AutoRunWithSystem(bool IsAutoRun, QString AppName, QString AppPath)
    {
        QSettings *reg = new QSettings(
            "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
            QSettings::NativeFormat);

        if (IsAutoRun) {
            reg->setValue(AppName, AppPath);
        } else {
            reg->setValue(AppName, "");
        }
    }

    //设置编码为UTF8
    static void SetUTF8Code()
    {
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QTextCodec::setCodecForLocale(codec);
        QTextCodec::setCodecForCStrings(codec);
        QTextCodec::setCodecForTr(codec);
#endif
    }

    //设置皮肤样式
    static void SetStyle(const QString &styleName)
    {
        QFile file(QString(":/Data/Css/%1.css").arg(styleName));
        file.open(QFile::ReadOnly);
        QString qss = QLatin1String(file.readAll());
        qApp->setStyleSheet(qss);
        qApp->setPalette(QPalette(QColor("#F0F0F0")));
    }

    //加载中文字符
    static void SetChinese(const QString &translatorName)
    {
        QTranslator *translator = new QTranslator(qApp);
        translator->load(QString(":/Data/Css/%1.qm").arg(translatorName));
        qApp->installTranslator(translator);
    }

    //判断是否是IP地址
    static bool IsIP(QString IP)
    {
        QRegExp RegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
        return RegExp.exactMatch(IP);
    }

    //显示信息框,仅确定按钮
    static void ShowMessageBoxInfo(const QString& strText)
    {
        //LMessageBox::Instance()->setMsgType(strText, 0);
        //LMessageBox::Instance()->show();
        LMessageBox *msgBox = new LMessageBox;
        msgBox->setMsgType(strText, 0);
        msgBox->show();

    }

    //显示警告框,仅确定按钮
    static void ShowMessageBoxWarning(const QString& strText)
    {
        //LMessageBox::Instance()->setMsgType(strText, 2);
        //LMessageBox::Instance()->show();
        LMessageBox *msgBox = new LMessageBox;
        msgBox->setMsgType(strText, 2);
        msgBox->show();

    }

    //显示错误框,仅确定按钮
    static void ShowMessageBoxError(const QString& strText)
    {
        //LMessageBox::Instance()->setMsgType(strText, 3);
        //LMessageBox::Instance()->show();
        LMessageBox *msgBox = new LMessageBox;
        msgBox->setMsgType(strText, 3);
        msgBox->show();

    }

    //显示询问框,确定和取消按钮
    static int ShowMessageBoxQuesion(const QString& strText)
    {
        //LMessageBox::Instance()->setMsgType(strText, 1);
        //LMessageBox::Instance()->show();
        LMessageBox *msgBox = new LMessageBox;
        msgBox->setMsgType(strText, 1);
        msgBox->show();
        return 0;
    }

    //延时
    static void Sleep(int sec)
    {
        QTime dieTime = QTime::currentTime().addMSecs(sec);
        while ( QTime::currentTime() < dieTime ) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
    }

    //窗体居中显示
    static void FormInCenter(QWidget *frm)
    {
        int frmX = frm->width();
        int frmY = frm->height();
        QDesktopWidget w;
        int deskWidth = w.width();
        int deskHeight = w.height();
        QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
        frm->move(movePoint);
    }

};

#endif // LCOMMON_H

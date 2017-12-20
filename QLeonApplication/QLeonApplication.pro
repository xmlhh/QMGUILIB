#-------------------------------------------------
#
# Project created by QtCreator 2017-12-20T11:21:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QLeonApplication
TEMPLATE = app


SOURCES += main.cpp\
        LeonWgt.cpp

HEADERS  += LeonWgt.h

FORMS    += LeonWgt.ui

RESOURCES += \
    res.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Lib/ -lQMGUILIB
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Lib/ -lQMGUILIBd

INCLUDEPATH += $$PWD/../Lib
DEPENDPATH += $$PWD/../Lib

#-------------------------------------------------
#
# Project created by QtCreator 2017-12-20T11:04:22
#
#-------------------------------------------------

QT       += widgets

TARGET = QMGUILIB
TEMPLATE = lib

DEFINES += QMGUILIB_LIBRARY

SOURCES += LDrawWgt.cpp \
    IconHelper.cpp \
    LDrawFilterWgt.cpp

HEADERS += LDrawWgt.h\
        qmguilib_global.h \
    IconHelper.h \
    LDrawFilterWgt.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LXRAMEBIN_ROOT =  ../Bin
LXRAMELIB_ROOT =  ../Lib

#配置debug和release模式
CONFIG(debug, debug|release) {
    unix: TARGET = $$join(TARGET,,,_debug)
    else: TARGET = $$join(TARGET,,,d)

    #LXRAMEBIN_ROOT =  ../Bin_d
}

INCLUDEPATH += ../Inc

win32{
    DESTDIR += $$LXRAMELIB_ROOT     #指定生成LIB的路径
    DLLDESTDIR = $$LXRAMEBIN_ROOT   #指定生成DLL的路径
}

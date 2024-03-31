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
    LDrawFilterWgt.cpp \
    LMessageBox.cpp

HEADERS += LDrawWgt.h\
        qmguilib_global.h \
    IconHelper.h \
    LDrawFilterWgt.h \
    LCommon.h \
    LMessageBox.h


FORMS += \
    LMessageBox.ui


unix {
    target.path = /usr/lib
    INSTALLS += target
}

#LXRAMEBIN_ROOT =  ../Bin
#LXRAMELIB_ROOT =  ../Lib

##配置debug和release模式
#CONFIG(debug, debug|release) {
#    unix: TARGET = $$join(TARGET,,,_debug)
#    else: TARGET = $$join(TARGET,,,d)

#    #LXRAMEBIN_ROOT =  ../Bin_d
#}

#win32{
#    DESTDIR += $$LXRAMELIB_ROOT     #指定生成LIB的路径
#    DLLDESTDIR = $$LXRAMEBIN_ROOT   #指定生成DLL的路径
#}


INCLUDEPATH += ../Inc

win32 {
    contains(QT_ARCH, i386) {
        CONFIG(release, debug|release):{
            DESTDIR += $$PWD/../Lib/x86     #指定生成LIB的路径
#            DLLDESTDIR = $$PWD/../Bin/x86   #指定生成DLL的路径
        } else:CONFIG(debug, debug|release):{
            TARGET = $$join(TARGET,,,d)
            DESTDIR += $$PWD/../Lib/x86
#            DLLDESTDIR = $$PWD/../Bin/x86
        }

    } else {
        CONFIG(release, debug|release):{
            DESTDIR += $$PWD/../Lib/x64
#            DLLDESTDIR = $$PWD/../Bin/x64
        } else:CONFIG(debug, debug|release):{
            TARGET = $$join(TARGET,,,d)
            DESTDIR += $$PWD/../Lib/x64
#            DLLDESTDIR = $$PWD/../Bin/x64
        }
    }
}

#-------------------------------------------------
#
# Project created by QtCreator 2014-10-06T14:05:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TomatoTimer
TEMPLATE = app


SOURCES += main.cpp\
        tomatotimerwindow.cpp

HEADERS  += tomatotimerwindow.h

FORMS    += tomatotimerwindow.ui

RESOURCES += \
    ttres.qrc


win32{
    RC_FILE = icon.rc
}else : macx {
    ICON = Tomato.icns
    greaterThan(QT_MAJOR_VERSION, 4): {
        QMAKE_MAC_SDK = "macosx"
        #"MacOSX10.9"
    }else: {
        #QMAKE_MAC_SDK += "/Xcode3.2.3/SDKs/MacOSX10.6.sdk"
        QMAKE_MAC_SDK += "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk/"
    }
}


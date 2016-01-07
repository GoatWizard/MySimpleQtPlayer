#-------------------------------------------------
#
# Project created by QtCreator 2015-12-18T21:25:07
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = MyPlayer
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

#INCLUDEPATH += $$PWD/thirdparty/win32/taglib/include/taglib
#LIBS += -L"$$_PRO_FILE_PWD_/thirdparty/win32/taglib/lib" -ltag -ltag_c

include(thirdparty\taglib\taglib.pro)

SOURCES += main.cpp\
        mainwindow.cpp \
    playlist_form.cpp \
    globals.cpp \
    info_pannel.cpp \
    myplayertreewidgetitem.cpp

HEADERS  += mainwindow.h \
    playlist_form.h \
    globals.h \
    info_pannel.h \
    myplayertreewidgetitem.h

FORMS    += mainwindow.ui \
    playlist_form.ui \
    info_pannel.ui

RESOURCES += \
    images.qrc

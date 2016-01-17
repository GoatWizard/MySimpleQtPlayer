#-------------------------------------------------
#
# Project created by QtCreator 2015-12-18T21:25:07
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia multimediawidgets

TARGET = qsmp
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS_RELEASE += -std=c++11 -O2 -march=native -mtune=native -ffast-math
include(thirdparty/taglib/taglib.pro)

SOURCES += main.cpp\
        mainwindow.cpp \
    playlist_form.cpp \
    globals.cpp \
    info_pannel.cpp \
    myplayertreewidgetitem.cpp \
    tworker.cpp

HEADERS  += mainwindow.h \
    playlist_form.h \
    globals.h \
    info_pannel.h \
    myplayertreewidgetitem.h \
    tworker.h

FORMS    += mainwindow.ui \
    playlist_form.ui \
    info_pannel.ui

RESOURCES += \
    images.qrc

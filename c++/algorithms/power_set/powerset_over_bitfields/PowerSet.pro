#-------------------------------------------------
#
# Project created by QtCreator 2013-02-13T12:43:14
#
#-------------------------------------------------

QT       += core

QT       -= gui

unix: {
    INCLUDEPATH += \
        . \
        /home/mehoggan/Devel/x86-fps/boost_1_50_0/include

    QMAKE_LFLAGS += -Wl,-rpath=/home/mehoggan/Devel/x86-fps/boost_1_50_0/lib

    LIBS += \
        -L/home/mehoggan/Devel/x86-fps/boost_1_50_0/lib \
        -lboost_system \
        -lboost_thread \
        -lboost_timer \
        -lz
}

TARGET = PowerSet
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

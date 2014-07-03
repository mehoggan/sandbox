#-------------------------------------------------
#
# Project created by QtCreator 2012-09-05T22:08:36
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = GridGL
TEMPLATE = app

unix: {
    INCLUDEPATH += \
        . \

    QMAKE_LFLAGS += -Wl,-rpath=lib

    LIBS += \
        -L./lib \
        -lboost_system \
        -lboost_date_time \
        -lboost_thread \
        -lboost_regex \
        -lpthread \
        -lGL \
        -lGLU
}

SOURCES += \
    glwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    singletontimer.cpp

HEADERS  += \
    mainwindow.h \
    glwidget.h \
    openglprimitives.h \
    singletontimer.h

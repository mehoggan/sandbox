TEMPLATE = app
CONFIG += console
CONFIG -= qt

LIBS += \
    -lrt \

SOURCES += main.cpp

HEADERS += \
    CallBack.h \
    TimerManager.h


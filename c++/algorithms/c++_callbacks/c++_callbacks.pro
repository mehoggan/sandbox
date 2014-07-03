TEMPLATE = app
CONFIG += console
CONFIG -= qt

LIBS += \
    -lrt \

SOURCES += main.cpp \
    CallMe.cpp

HEADERS += \
    CallBack.h \
    TimerManager.h \
    CallMe.h


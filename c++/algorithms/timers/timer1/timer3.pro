TEMPLATE = app
CONFIG += console
CONFIG -= qt

LIBS += \
    -lrt \

SOURCES += main.cpp \
    timer.cpp

HEADERS += \
    timer.h


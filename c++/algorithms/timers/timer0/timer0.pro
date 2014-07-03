TEMPLATE = app
CONFIG += console
CONFIG -= qt
CONFIG += threads

LIBS += \
    -lrt

HEADERS += \
    TimerManager.h

SOURCES += \
    main.cpp \
    TimerManager.cpp



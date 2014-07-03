TEMPLATE = app
CONFIG += console
CONFIG -= qt
CONFIG += threads

LIBS += \
    -lrt \
    -lXext \
    -lX11 \
    -lGLU

INCLUDEPATH += \

HEADERS += \
    RendererGL.h \
    TimerManager.h \
    GlxWnd.h \
    TimerManager.h

SOURCES += \
    linux_main.cpp \
    RendererGL.cpp \
    TimerManager.cpp

OTHER_FILES +=


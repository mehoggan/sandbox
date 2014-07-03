#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <stdio.h>
#include <string.h>

#ifdef WIN32
    #include <Windows.h>
    #include <Windowsx.h>
    static int appCmdShow = 0;
#else
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <stdexcept>
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
#endif
#endif

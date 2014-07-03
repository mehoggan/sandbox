#ifndef FWOPENGLDEVICE_H
#define FWOPENGLDEVICE_H

#include "FWGlobals.h"
#include <GL/gl.h>
#ifdef WIN32
#elif __linux__
#include <GL/glx.h>
#endif
class FWWindow;

class FWOpenGLDevice
{
private:
    FWWindow *win;
#ifdef WIN32
    PIXELFORMATDESCRIPTOR pfd;
    HGLRC hGLRC;
#elif __linux__
    struct GlxDevice
    {
        XVisualInfo *xVisualInfo;
        Colormap xColorMap;
        GLXContext glxContext;
    } glxDevice;
#endif
public:
    FWOpenGLDevice(FWWindow *win);
    ~FWOpenGLDevice();
#ifdef WIN32
    HGLRC GetDevice();
#elif __linux__
    GlxDevice *GetDevice();
#endif
    void BeginScene();
    void PresentScene();
    void Resize(unsigned int width, unsigned int height);
};

#endif

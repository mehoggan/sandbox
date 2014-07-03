#include "FWOpenGLDevice.h"
#include "FWGLExtensions.h"
#include "FWWindow.h"

/*
 * Remove: for testing only
 */
#include "iostream"

FWOpenGLDevice::FWOpenGLDevice(FWWindow *win) :
    win(win)
{
#ifdef WIN32
	hGLRC = NULL;
	::ZeroMemory(&pfd, sizeof(pfd));
    pfd.nSize = sizeof( pfd );
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
                  PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    int iFormat = ChoosePixelFormat(win->getHDC(), &pfd);
    SetPixelFormat(win->getHDC(), iFormat, &pfd);
#elif __linux__
    glxDevice.glxContext = NULL;
    static int glx_attributes[10];
    static int glx_attributes_indexes = 0;    

    Display *dpy = FWApplication::GetMainDisplay();
    glx_attributes[glx_attributes_indexes++] = GLX_RED_SIZE;
    glx_attributes[glx_attributes_indexes++] = 1;
    glx_attributes[glx_attributes_indexes++] = GLX_GREEN_SIZE;
    glx_attributes[glx_attributes_indexes++] = 1;
    glx_attributes[glx_attributes_indexes++] = GLX_BLUE_SIZE;
    glx_attributes[glx_attributes_indexes++] = 1;
    glx_attributes[glx_attributes_indexes++] = GLX_ALPHA_SIZE; 
    glx_attributes[glx_attributes_indexes++] = 1;
    glx_attributes[glx_attributes_indexes++] = GLX_DOUBLEBUFFER; 
    glx_attributes[glx_attributes_indexes++] = True;

    int number_of_configs = 0;
    GLXFBConfig *configs = NULL;
    
    configs = glXChooseFBConfig(dpy, DefaultScreen(dpy), glx_attributes, &number_of_configs);

    if (configs == NULL) {
        throw std::runtime_error("Failed to create Frame Buffer configuration");
    }
    
    //glxDevice.xVisualInfo = glXChooseVisual(dpy, DefaultScreen(dpy), glx_attributes);
    glxDevice.xVisualInfo = glXGetVisualFromFBConfig(dpy, *(configs));

    if (glxDevice.xVisualInfo == NULL)
        throw "Failed to create glxVisual";

    glxDevice.xColorMap = XCreateColormap(
                dpy,
                RootWindow(dpy, glxDevice.xVisualInfo->screen),
                glxDevice.xVisualInfo->visual,
                AllocNone
                );
#endif
}

FWOpenGLDevice::~FWOpenGLDevice()
{
#ifdef WIN32
    ::wglMakeCurrent(NULL, NULL);
    ::wglDeleteContext(hGLRC);
#elif __linux__
    glXMakeCurrent(FWApplication::GetMainDisplay(), None, NULL);
    glXDestroyContext(FWApplication::GetMainDisplay(), glxDevice.glxContext);
    glxDevice.glxContext = NULL;
#endif
}

#ifdef WIN32
HGLRC FWOpenGLDevice::GetDevice()
{
    return hGLRC;
}
#elif __linux__
FWOpenGLDevice::GlxDevice *FWOpenGLDevice::GetDevice()
{
    return &glxDevice;
}
#endif

void FWOpenGLDevice::BeginScene()
{
#ifdef WIN32
	if (hGLRC == NULL)
	{
		HDC lhDC = win->getHDC();
		hGLRC = ::wglCreateContext(lhDC);
		::wglMakeCurrent(win->getHDC(), hGLRC);
                FWGLExtensions::loadGLExtensions();
	}
	else
	{
		::wglMakeCurrent(win->getHDC(), hGLRC);
	}
#elif __linux__
    if (glxDevice.glxContext == NULL)
    {
        glxDevice.glxContext = glXCreateContext(
                FWApplication::GetMainDisplay(),
                glxDevice.xVisualInfo,
                None,
                True
                );
        glXMakeCurrent(
                    FWApplication::GetMainDisplay(),
                    (*win->getWindow()),
                    glxDevice.glxContext
                    );
                    FWGLExtensions::loadGLExtensions();
    }
    else
    {
        glXMakeCurrent(
                    FWApplication::GetMainDisplay(),
                    (*win->getWindow()),
                    glxDevice.glxContext
                    );
    }
#endif
}

void FWOpenGLDevice::PresentScene()
{
#ifdef WIN32
    ::SwapBuffers(win->getHDC());
#elif __linux__
    glXSwapBuffers(
                FWApplication::GetMainDisplay(),
                (*win->getWindow())
                );
    glXMakeContextCurrent(FWApplication::GetMainDisplay(), None, None, NULL);
#endif
}

void FWOpenGLDevice::Resize(unsigned int /*width*/, unsigned int /*height*/)
{
}

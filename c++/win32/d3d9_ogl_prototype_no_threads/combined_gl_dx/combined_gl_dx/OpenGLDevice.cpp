#include "OpenGLDevice.h"
#include "Window.h"

OpenGLDevice::OpenGLDevice(Window *win) :
    win(win)
{
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
	hGLRC = ::wglCreateContext(win->getHDC());
}

OpenGLDevice::~OpenGLDevice()
{
	::wglMakeCurrent(NULL, NULL);
	::wglDeleteContext(hGLRC);
}

HGLRC OpenGLDevice::GetDevice()
{
	return hGLRC;
}

void OpenGLDevice::BeginScene()
{
	::wglMakeCurrent(win->getHDC(), hGLRC);
}

void OpenGLDevice::PresentScene()
{
	::SwapBuffers(win->getHDC());
}
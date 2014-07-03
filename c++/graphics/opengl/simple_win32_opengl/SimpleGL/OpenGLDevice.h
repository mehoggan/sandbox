#ifndef OPENGLDEVICE_H_
#define OPENGLDEVICE_H_

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Window;

class OpenGLDevice 
{
public:
	OpenGLDevice(Window *win);
	~OpenGLDevice();
	HGLRC GetDevice();
	void BeginScene();
	void PresentScene();
private:
	Window *win;
	PIXELFORMATDESCRIPTOR pfd;
	HGLRC hGLRC;
};

#endif

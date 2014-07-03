#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h> 
#include <sstream>
#include <iostream>
#include <cstring>
#include <GL/gl.h>
#include <GL/glu.h>

#ifndef CONTROLLER_GL
#define CONTROLLER_GL
/************************************************************************/
/* 	This class will handle all input to a given window	and then 		*/
/*	delegate to the ViewGL and ModelGL object associated with it		*/
/************************************************************************/
class ControllerGL {
	public:
		ControllerGL();
		ControllerGL(HWND hwnd);
		~ControllerGL();
		void setHandle(HWND hwnd);
		bool createRenderThread();
		void handleResize(int width, int height, WPARAM type);                         
	private:
		static DWORD WINAPI threadFunction(void* pArg);      
		void runThread();
		 
		HWND hwnd;
		HANDLE threadHandle;
		DWORD  threadId;
		int loopFlag;
		int resizeFlag;
		int wndWidth;
		int wndHeight;
		HDC hdc;                                        								// handle to device context
		HGLRC hglrc;                                    								// handle to OpenGL rendering context
		PIXELFORMATDESCRIPTOR pfd;														// pixel format descriptor
		INT pixelFormatDescriptor;														// flag for valid PIXELFORMATDESCRIPTOR
};
#endif	//	CONTROLLER_GL

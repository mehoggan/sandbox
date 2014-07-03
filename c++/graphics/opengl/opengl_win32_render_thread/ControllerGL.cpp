#include "ControllerGL.h"

using namespace std;

ControllerGL::ControllerGL() {
	this->resizeFlag = 0;
	this->loopFlag = 1;
}

ControllerGL::~ControllerGL() {
}

void ControllerGL::setHandle(HWND hwnd){
	this->hwnd = hwnd;
}

void ControllerGL::runThread(){
	this->hglrc = ::wglCreateContext(this->hdc);
	::wglMakeCurrent(this->hdc, this->hglrc);
	
	glShadeModel(GL_SMOOTH);                        	// shading mathod: GL_SMOOTH or GL_FLAT
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
	glClearColor(0, 0, 0, 0);                       	// background color
    glClearStencil(0);                              	// clear stencil buffer
    glClearDepth(1.0f);                             	// 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);
	
	/*	
	 *	Main Rendering Loop
	 */
	while(loopFlag){
		//*
		::Sleep(10);
		if(this->resizeFlag > 0){
			glViewport(0, 0, (GLsizei)(this->wndWidth), (GLsizei)(this->wndHeight));
			
			float aspectRatio = ((float)(this->wndWidth)/(this->wndHeight));
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();		
			gluPerspective(50.0f, aspectRatio, 1.0f, 100000.0f);
			
			this->resizeFlag = 0;
		}
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0, 0, 10, 0, 0, -10, 0, 1, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
		glBegin(GL_TRIANGLES);
			glNormal3f(0, 0, 1);
			glColor3f(1, 0, 0);
			glVertex3f(3, -2, 0);
			glColor3f(0, 1, 0);
			glVertex3f(0, 2, 0);
			glColor3f(0, 0, 1);
			glVertex3f(-3, -2, 0);
		glEnd();
		glPopMatrix();
		::SwapBuffers(this->hdc);			
	}
	
	/*	
	 *	END OF MAIN RENDERING LOOP
	 */
	::wglMakeCurrent(NULL, NULL);
	::CloseHandle(this->threadHandle);
}

bool ControllerGL::createRenderThread(){
	bool continue_game = true;
	this->hdc = ::GetDC(this->hwnd);
	this->pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR); this->pfd.nVersion = 1; 
	this->pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;	
	this->pfd.iPixelType = PFD_TYPE_RGBA; this->pfd.cColorBits = 24;														
	this->pfd.cRedBits = 0; this->pfd.cGreenBits = 0; this->pfd.cBlueBits = 0; this->pfd.cAlphaBits = 0;
	this->pfd.cRedShift = 0; this->pfd.cGreenShift = 0; this->pfd.cBlueShift = 0; this->pfd.cAlphaShift = 0;
	this->pfd.cAccumBits = 0; this->pfd.cAccumRedBits = 0; this->pfd.cAccumGreenBits = 0; this->pfd.cAccumBlueBits = 0;
	this->pfd.cDepthBits = 16; this->pfd.cStencilBits = 0; this->pfd.cAuxBuffers = 0; this->pfd.iLayerType = 0;
	this->pfd.bReserved = 0; this->pfd.dwLayerMask = 0; this->pfd.dwVisibleMask = 0; this->pfd.dwDamageMask = 0;
	this->pixelFormatDescriptor = ::ChoosePixelFormat(this->hdc, &(pfd));
	if(!(this->pixelFormatDescriptor)){
		::MessageBox(0, "Cannot set a suitable pixel format.", "Error", MB_ICONEXCLAMATION | MB_OK);
		::ReleaseDC(this->hwnd, this->hdc); 
	}
	::SetPixelFormat(this->hdc, this->pixelFormatDescriptor, &(pfd));
	
	/*
	 *	CREATE THE RENDER THREAD -- IF THREAD NOT CREATED CORRECTLY DO NOT CONTINUE GAME
	 */
	//*
	#pragma warning(disable: 4355)
	threadHandle = ::CreateThread( NULL, 0, ControllerGL::threadFunction, this, 0, &threadId);  
	#pragma warning(default: 4355)
	if(!threadHandle) continue_game = false;
	else this->loopFlag = 1;
	//*/
	/*
	 *	END OF CREATE THE RENDER THREAD
	 */
	
	return continue_game;
}

DWORD WINAPI ControllerGL::threadFunction(void* param){
	((ControllerGL*)param)->runThread();
	return 0;
} 

void ControllerGL::handleResize(int width, int height, WPARAM type){
	this->resizeFlag = 1;
	this->wndWidth = width;
	this->wndHeight = height;
}
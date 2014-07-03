#include "Window.h"
#include "OpenGLDevice.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <windows.h>

struct TransformedColouredVertex
{
    float red, green, blue;
	float x, y, z;
} vertices[] =
{
    {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f},
	{1.0f, 0.0f, 0.0f, 0.87f, -0.5f, 0.0f},
	{1.0f, 0.0f, 0.0f, -0.87f, -0.5f, 0.0f}
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

// Globals
Window* win;
OpenGLDevice* ogl_device;
static float theta = 0;
static int width = 800, height = 600;
bool resizeFlag = false;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevtInst, LPSTR cmdParam, INT cmdShow) 
{
    win = new Window(hInst, WndProc, width, height);
	win->Register();									//	Register the main window
	win->Show(cmdShow, hInst);							//	Display main window
	ogl_device = new OpenGLDevice(win);
	MSG msg;												
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE )  )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		} 
		else 
		{	
			ogl_device->BeginScene();
			if(resizeFlag){
			    glViewport(0, 0, (GLsizei)(width), (GLsizei)(height));
			    float aspectRatio = ((float)(width)/(height));
			    glMatrixMode(GL_PROJECTION);
			    glLoadIdentity();		
			    gluPerspective(50.0f, aspectRatio, 1.0f, 100000.0f);
			    resizeFlag = false;
		    }
		    glMatrixMode(GL_MODELVIEW);
		    glLoadIdentity();
		    gluLookAt(0, 0, 5, 0, 0, -10, 0, 1, 0);
			glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
			glClear( GL_COLOR_BUFFER_BIT );
			glBegin( GL_TRIANGLES );
			    for (int i = 0; i < 3; i++) {
			        glColor3f( vertices[i].red, vertices[i].green, vertices[i].blue); 
			        glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
			    }
			glEnd();
			ogl_device->PresentScene();
		}
	}
	if (win != NULL) 
    { 
	    delete win;
		win = NULL; 
	}
	if (ogl_device != NULL) 
	{ 
		delete ogl_device; 
		ogl_device = NULL; 
	}
	return (int)msg.wParam; 
}
														
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch(message)
	{
	case WM_CREATE:
		break;
	case WM_SIZE:
		resizeFlag = true;
		width = LOWORD(lParam);
	    height = HIWORD(lParam);
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	default:
		return ::DefWindowProcA(hwnd, message, wParam, lParam);
	}
	return ::DefWindowProcA(hwnd, message, wParam, lParam);
}
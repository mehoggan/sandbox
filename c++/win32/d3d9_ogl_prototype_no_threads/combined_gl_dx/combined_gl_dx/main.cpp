#include "Window.h"
#include "D3DDevice.h"
#include "OpenGLDevice.h"
#include <GL/gl.h>
#include <GL/glu.h>

#ifdef _DX_
struct TransformedColouredVertex 
{
    float x, y, z, rhw;
    DWORD colour;
    static const DWORD FORMAT = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
    static const int STRIDE_SIZE = 20;
} vertices[] = 
{
    { 300.0f, 75.0f, 0.0f, 1.0f, 0xffff0000 },
    { 525.0f, 525.0f, 0.0f, 1.0f, 0xffff0000 },
    { 75.0f, 525.0f, 0.0f, 1.0f, 0xffff0000 }
};
#else
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
#endif

// Prototypes
LRESULT CALLBACK WndProc(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);

// Globals
Window *win;

#ifdef _DX_
D3DDevice *d3d_device;
#else
OpenGLDevice* ogl_device;
#endif

static float theta = 0;
static int width = 800, height = 600;
bool resizeFlag = false;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevtInst, LPSTR cmdParam, INT cmdShow)
{
	win = new Window(hInst, WndProc, width, height);	
	win->Register();									//	Register the main window
	win->Show(cmdShow, hInst);							//	Display main window

#ifdef _DX_
	d3d_device = new D3DDevice(win); 
	d3d_device->GetDevice().SetFVF(vertices[0].FORMAT);
#else
	ogl_device = new OpenGLDevice(win);
#endif

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT) 
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} 
		else
	    {
#ifdef _DX_
			d3d_device->BeginScene();
			d3d_device->GetDevice().Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
	        d3d_device->GetDevice().DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, vertices, vertices[0].STRIDE_SIZE);
	        d3d_device->PresentScene();
#else
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
#endif
		}
	}
	if (win != NULL) 
    { 
	    delete win;
		win = NULL; 
	}
#ifdef _DX_
	if (d3d_device != NULL) 
	{ 
		delete d3d_device; 
		d3d_device = NULL; 
	}
#else
	if (ogl_device != NULL) 
	{ 
		delete ogl_device; 
		ogl_device = NULL; 
	}
#endif
	return EXIT_SUCCESS;
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



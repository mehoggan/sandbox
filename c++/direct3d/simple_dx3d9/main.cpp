#include "Window.h"
#include "D3DDevice.h"

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

LRESULT CALLBACK WndProc(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);

// Globals
Window *win;
D3DDevice *d3d_device;
static float theta = 0;
static int width = 800, height = 600;
bool resizeFlag = false;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevtInst, LPSTR cmdParam, INT cmdShow)
{
	win = new Window(hInst, WndProc, width, height);	
	win->Register();									//	Register the main window
	win->Show(cmdShow, hInst);							//	Display main window
	d3d_device = new D3DDevice(win->getHWND(), win->getClientWidth(), win->getClientHeight()); 
	d3d_device->GetDevice().SetFVF(vertices[0].FORMAT);
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
			d3d_device->BeginScene();
			d3d_device->GetDevice().Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
	        d3d_device->GetDevice().DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, vertices, vertices[0].STRIDE_SIZE);
	        d3d_device->PresentScene();
		}
	}
	if (win != NULL) 
    { 
	    delete win;
		win = NULL; 
	}
	if (d3d_device != NULL) 
	{ 
		delete d3d_device; 
		d3d_device = NULL; 
	}
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



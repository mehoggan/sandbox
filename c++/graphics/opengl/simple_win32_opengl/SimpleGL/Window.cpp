#include "Window.h"
#include <GL/gl.h>
#include <GL/glu.h>

Window::Window(HINSTANCE hInstance, WNDPROC winProc, int width, int height) :
        clientWidth(width),
		clientHeight(height),
		hWnd(NULL),
		hDC(NULL)
{
	wc.cbSize        	= sizeof(WNDCLASSEX);
    wc.style         	= 0;
    wc.lpfnWndProc   	= winProc;
    wc.cbClsExtra    	= 0;
    wc.cbWndExtra    	= 0;
    wc.hInstance     	= hInstance;
    wc.hIcon         	= LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       	= LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground 	= (HBRUSH)GetStockObject( WHITE_BRUSH );
    wc.lpszMenuName  	= TEXT("GenericAppMenu");
    wc.lpszClassName 	= TEXT("myWindowClass");
    wc.hIconSm       	= LoadIcon(NULL, IDI_APPLICATION);
}

Window::~Window()
{
	::ReleaseDC(hWnd, hDC);
}

void Window::Register() 
{
	if(!RegisterClassEx(&wc)){
        ::MessageBox(NULL, TEXT("Window Registration Failed!"), TEXT("Error!"), MB_ICONEXCLAMATION | MB_OK);
        exit(0);
    }
}

void Window::Show(INT cmdShow, HINSTANCE hInstance) 
{
    hWnd = ::CreateWindowEx(	WS_EX_CLIENTEDGE,									// Window Style
								TEXT("myWindowClass"),								// name of a registered window class
								TEXT("The title of my window"),						// window caption
								WS_OVERLAPPEDWINDOW,								// window style
								CW_USEDEFAULT,										// x position
								CW_USEDEFAULT,										// y position
								this->clientWidth,									// witdh
								this->clientHeight,									// height
								NULL,												// handle to parent window
								NULL,												// handle to menu
								hInstance,											// application instance
								NULL
							);
	
	if(hWnd == NULL)
	{
        ::MessageBox(NULL, TEXT("Window Creation Failed!"), TEXT("Error!"), MB_ICONEXCLAMATION | MB_OK);
        exit(1);
    }
	this->hDC = ::GetDC(hWnd);
	::ShowWindow(hWnd, cmdShow);									
	::UpdateWindow(hWnd);
}

int Window::getClientWidth()
{
	return this->clientWidth;
}

int Window::getClientHeight()
{
	return this->clientHeight;
}

HWND Window::getHWND()
{
	return this->hWnd;
}

HDC  Window::getHDC() 
{
	return this->hDC;
}
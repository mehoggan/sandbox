#include "WinMaker.h"
#include "ControllerGL.h"
#include <GL/gl.h>
#include <GL/glu.h>

WinMaker::WinMaker() {
}

WinMaker::WinMaker(HINSTANCE hInstance, WNDPROC winProc, int width, int height, ControllerGL* cntrlGL) {
	this->clientWidth	= width;
	this->clientHeight	= height;
	this->graphixGL 	= cntrlGL;
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
    wc.lpszClassName 	= "myWindowClass";
    wc.hIconSm       	= LoadIcon(NULL, IDI_APPLICATION);
}

void WinMaker::Register() {
	if(!RegisterClassEx(&wc)){
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        exit(0);
    }
}

void WinMaker::Show(INT cmdShow, HINSTANCE hInstance) {
				
	/*
	char output[256];
	sprintf(output, "WM_CREATE Address: %x", this->graphixGL);
	::MessageBox(0, output, "Error", MB_ICONEXCLAMATION | MB_OK);
	//*/
				
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
								(LPVOID)this->graphixGL								// window creation data
							);
	
	if(hWnd == NULL){
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        exit(1);
    }
	::ShowWindow(hWnd, cmdShow);									
	::UpdateWindow(hWnd);
}

int WinMaker::getClientWidth(){
	return this->clientWidth;
}

int WinMaker::getClientHeight(){
	return this->clientHeight;
}

HWND WinMaker::getHWND(){
	return this->hWnd;
}
//#ifndef _WINDOW_H
//#define _WINDOW_H
//
//#include <windows.h>
//
//class Window {
//public:
//	Window(WNDPROC WndProc, LPCTSTR title, int x, int y, int width, int height);
//	~Window();
//    HWND getHandle() { return window; }
//	void show() { 
//		::ShowWindow(window, SW_SHOWDEFAULT); 
//	}
//
//protected:
//	WNDCLASS windowClass;
//	HWND window;
//};
//#endif

#ifndef WINDOW_H_
#define WINDOW_H_

#include <windows.h>
#include <stdio.h>

class Window {
public:
	Window(HINSTANCE hInstance, WNDPROC WndProc, int width, int height);
	~Window();
	void Register();
	void Show(INT cmdShow, HINSTANCE hInstance);
	int getClientWidth();
	int getClientHeight();
	HWND getHWND();
	HDC  getHDC();
private:
	HWND hWnd;
	HDC hDC;
	WNDCLASSEX wc;										
	int clientWidth;
	int clientHeight;
};
#endif	//	WINMAKER
#ifndef WINDOW_H_
#define WINDOW_H_

#include <windows.h>
#include <stdio.h>

class Window {
public:
	Window(HINSTANCE hInstance, WNDPROC winProc, int width, int height);
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
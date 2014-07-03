#ifndef DXWINDOW_H_
#define DXWINDOW_H_

#include <windows.h>

class DXWindow
{
public:
	DXWindow(HINSTANCE hInstance);
	~DXWindow();
	bool Register();
	bool Create(HINSTANCE hInstance, int nCmdShow);
private:
	WNDCLASSEX wcex;
	HWND hwnd;
	void SetHWND(HWND);
	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK MsgRouter(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
};

#endif
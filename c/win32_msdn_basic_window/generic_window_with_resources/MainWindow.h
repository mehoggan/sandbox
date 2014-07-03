#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <windows.h>

class MainWindow
{
public:
	MainWindow(HINSTANCE hInstance);
	~MainWindow();
	void Register();
	void Run(HINSTANCE hInstance,  int nCmdShow);
private:
	WNDCLASS wc;
	HWND hWnd;
};

#endif //MAINWINDOW_H_
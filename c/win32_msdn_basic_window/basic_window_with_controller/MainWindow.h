#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <windows.h>
#include "IController.h"

class MainWindow
{
public:
	MainWindow(HINSTANCE hInstance, IController* cntrl);
	~MainWindow();
	void Register();
	void Run(HINSTANCE hInstance,  int nCmdShow);
private:
	WNDCLASSEX wc;
	HWND hWnd;
	IController* cntrl;
};

#endif //MAINWINDOW_H_
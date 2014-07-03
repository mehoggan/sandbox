//This is a Simple Window
#include <windows.h>
#include "MainWindow.h"

void MessageLoop();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MainWindow* m_wnd = new MainWindow(hInstance);
	m_wnd->Register();
	m_wnd->Run(hInstance, nCmdShow);

	MessageLoop();
}

void MessageLoop()
{
	MSG msg;

	while(GetMessage(&msg, NULL, 0, 0) != 0) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
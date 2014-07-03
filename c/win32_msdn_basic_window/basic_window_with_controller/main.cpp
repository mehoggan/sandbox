#define _WIN32_DCOM
#include <windows.h>
#include <malloc.h>
#include <objbase.h>
#include "MainWindow.h"
#include "IController.h"
#include "MainController.h"

int MessageLoop();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//	Initilize COM Library To Accept Multiple Threads
	//HRESULT hRslt = CoInitializeEx(NULL, COINIT_MULTITHREADED);

	MainController cntrl;

	MainWindow* m_wnd = new MainWindow(hInstance, &cntrl);
	m_wnd->Register();
	m_wnd->Run(hInstance, nCmdShow);

	int exit_status = MessageLoop();
}

int MessageLoop()
{
	MSG msg;

	while(GetMessage(&msg, NULL, 0, 0) != 0) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
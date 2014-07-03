#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "DXWindow.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{	
	DXWindow dxwnd1(hInstance);
	dxwnd1.Register();
	dxwnd1.Create(hInstance, nCmdShow);

	DXWindow dxwnd2(hInstance);
	dxwnd2.Create(hInstance, nCmdShow);

	MSG msg = {0};
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
#include <windows.h>
#include <stdio.h>

class ControllerGL;

#ifndef WINMAKER
#define WINMAKER

class WinMaker {
	public:
		WinMaker();
		WinMaker(HINSTANCE hInstance, WNDPROC winProc, int width, int height, ControllerGL* graphixGL);
		void Register();
		void Show(INT cmdShow, HINSTANCE hInstance);
		int getClientWidth();
		int getClientHeight();
		HWND getHWND();
	private:
		HWND hWnd;										//Windows Data Type
		WNDCLASSEX wc;									//Windows Structure	
		int clientWidth;
		int clientHeight;
		ControllerGL* graphixGL;
};
#endif	//	WINMAKER
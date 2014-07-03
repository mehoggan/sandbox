#include "WinMaker.h"
#include "ControllerGL.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

/************************************************************************/
/* Proto Types For Global Functions										*/
/************************************************************************/
void initializeApp(HINSTANCE hInst, HINSTANCE hPrevtInst, LPSTR cmdParam, INT cmdShow);
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

/************************************************************************/
/* Global Variable Section												*/
/************************************************************************/
WinMaker* 		winmaker;									//	Used to create main window
ControllerGL* 	cntrl;										// Will handle all open GL evnets																																									// aspect ratio for main window

/************************************************************************/
/* Entry into program													*/
/************************************************************************/
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevtInst, LPSTR cmdParam, INT cmdShow) {
	initializeApp(hInst, hPrevtInst, cmdParam, cmdShow);	// Create main window
	MSG msg;												
	while(::GetMessage(&msg, 0, 0, 0) > 0) {				// Main message loop
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
	return (int)msg.wParam; 
}

/************************************************************************/
/*	Initialize All Important App Variables								*/
/************************************************************************/
void initializeApp(HINSTANCE hInst, HINSTANCE hPrevtInst, LPSTR cmdParam, INT cmdShow){
	cntrl = new ControllerGL();
	winmaker=new WinMaker(hInst, WindowProcedure, 800, 600, cntrl);
	winmaker->Register();									//	Register the main window
	winmaker->Show(cmdShow, hInst);							//	Display main window
}
														
/************************************************************************/
/* Main Window Call Back Function										*/
/************************************************************************/
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static ControllerGL* ctrl;
	ctrl = (ControllerGL*)::GetWindowLongPtr(hwnd, GWL_USERDATA);
	
	if(message == WM_NCCREATE){
		ctrl = (ControllerGL*)(((CREATESTRUCT*)lParam)->lpCreateParams);
		ctrl->setHandle(hwnd);
		::SetWindowLongPtr(hwnd, GWL_USERDATA, (LONG_PTR)ctrl);
	}else{
		switch(message) {
			case WM_CREATE: {
				int threadStatus = ctrl->createRenderThread();		
				if(!threadStatus) ::PostQuitMessage(0);
				break;
			}
			case WM_SIZE: {
				ctrl->handleResize(LOWORD(lParam), HIWORD(lParam), wParam);
				break;
			}
			case WM_DESTROY: {
				::ShowCursor(TRUE);
				::PostQuitMessage(0);
			}
		}
	}
	return ::DefWindowProc(hwnd, message, wParam, lParam);
}
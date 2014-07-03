#ifndef MAINWNDPROC_H_
#define MAINWNDPROC_H_

#include "IController.h"

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;

	static IController *cntrl;
	cntrl = (IController*)::GetWindowLongPtr(hWnd, GWL_USERDATA);

	if(uMsg == WM_NCCREATE)
	{
		cntrl = (IController*)(((CREATESTRUCT*)lParam)->lpCreateParams);
        ::SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)cntrl);
		cntrl->CheckStatus();
        return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	switch(uMsg) 
	{
		case WM_CREATE:
		{
		}
		case WM_PAINT:
		{			 
			hDC = BeginPaint( hWnd, &ps );
			TextOut( hDC, 10, 10, TEXT("Hello, Windows!"), 15 );
			EndPaint( hWnd, &ps );
			return 0;
		}
		case WM_DESTROY:
		{
			PostQuitMessage( 0 );
			return 0;
		}
		default:
			return DefWindowProc( hWnd, uMsg, wParam, lParam );
	}
}

#endif //MAINWNDPROC_H_
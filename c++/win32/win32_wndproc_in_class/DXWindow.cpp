#include <stdlib.h>
#include <stdio.h>
#include "DXWindow.h"

DXWindow::DXWindow(HINSTANCE hInstance)
{
	wcex.cbSize			=	sizeof(WNDCLASSEX);
	wcex.style			=	CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	=	MsgRouter;
	wcex.cbClsExtra		=	0;
	wcex.cbWndExtra		=	0;
	wcex.hInstance		=	hInstance;
	wcex.hIcon			=	0;
	wcex.hCursor		=	::LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground  =	(HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	=	0;
	wcex.lpszClassName	=	"DXWindow";
	wcex.hIconSm		=	0;
}

DXWindow::~DXWindow()
{
}

void DXWindow::SetHWND(HWND hwnd)
{
	this->hwnd = hwnd;
}


LRESULT CALLBACK DXWindow::MsgRouter(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	DXWindow* WND;
	
	if(message == WM_NCCREATE)
	{
		WND = reinterpret_cast<DXWindow*>(((LPCREATESTRUCT)lparam)->lpCreateParams);
		::SetWindowLongPtr(hwnd, GWL_USERDATA, (LONG)(reinterpret_cast<DXWindow*>(WND)));
	}
	else
	{
		WND = reinterpret_cast<DXWindow*>(::GetWindowLongPtr(hwnd, GWL_USERDATA));
	}
    return WND->WndProc(hwnd, message, wparam, lparam);
}


LRESULT CALLBACK DXWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch(uMsg)
	{
		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		case WM_LBUTTONDOWN:
		{
			char msg[512];
			sprintf_s(msg, "Left Click in %x", hWnd);
			::MessageBox(0, msg, msg, MB_OK);
		}
		default:
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam); 
		}
	}
	return 0;
}

bool DXWindow::Register()
{
	if(!::RegisterClassEx(&wcex))
	{
		char error[512];
		sprintf_s(error, "Failed to register class");
		MessageBox(0, error, error, MB_OK);
		exit(0);
	}
	return TRUE;
}

bool DXWindow::Create(HINSTANCE hInstance, int nCmdShow)
{
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,
						  "DXWindow",
						  "MainWindow",
						  WS_OVERLAPPEDWINDOW,
						  10,
						  10,
						  400,
						  600,
						  0,
						  0,
						  hInstance,
						  0);

	if(!hwnd)
	{
		char error[512];
		sprintf_s(error, "Failed to create window");
		MessageBox(0, error, error, MB_OK);
		exit(0);
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	return TRUE;
}

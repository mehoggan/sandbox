#include "MainWindow.h"
#include "MainWndProc.h"

MainWindow::MainWindow(HINSTANCE hInstance)
{
	wc.lpszClassName = TEXT("GenericAppClass");
	wc.lpfnWndProc = MainWndProc;
	wc.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = TEXT("GenericAppMenu");
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
}

MainWindow::~MainWindow()
{
}

void MainWindow::Register()
{
	RegisterClass(&wc);
}

void MainWindow::Run(HINSTANCE hInstance, int nCmdShow)
{
	hWnd = CreateWindow(TEXT("GenericAppClass"),
						TEXT("Generic Application"),
						WS_OVERLAPPEDWINDOW|WS_HSCROLL|WS_VSCROLL,
						0,
						0,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						NULL,
						NULL,
						hInstance,
						NULL);

	ShowWindow( hWnd, nCmdShow );
}

#include "MainWindow.h"
#include "MainWndProc.h"

MainWindow::MainWindow(HINSTANCE hInstance, IController* cntrl)
{
	wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = MainWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = TEXT("GenericAppMenu");
    wc.lpszClassName = "myWindowClass";
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

	this->cntrl = cntrl;
}

MainWindow::~MainWindow()
{
}

void MainWindow::Register()
{
	if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        exit(0);
    }
}

void MainWindow::Run(HINSTANCE hInstance, int nCmdShow)
{
	MessageBox(NULL, "Creating Window", "Checking...", MB_OK);
	
	hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("myWindowClass"), 
		TEXT("The title of my window"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 
		240, 120, NULL, NULL, hInstance, this->cntrl);

	MessageBox(NULL, "Window Created", "Status", MB_OK);

    if(hWnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        exit(0);
    }

	ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
}

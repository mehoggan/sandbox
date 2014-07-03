#include "FWWindow.h"
#include "FWEvent.h"
#include "FWOpenGLDevice.h"
#ifdef WIN32
#include "FWD3DDevice.h"
#elif __linux__
#include "FWCallBack.h"
#include "FWLinuxTimer.h"
#endif

FWOpenGLDevice *FWWindow::oglDevice = NULL;
#ifdef WIN32
FWD3DDevice *FWWindow::d3dDevice = NULL;
#elif __linux__
FWCallBack<FWWindow, int, unsigned int> *FWWindow::call_back = NULL;
FWLinuxTimer<FWWindow> *FWWindow::linux_timer = NULL;
#endif

FWWindow::FWWindow(int width, int height) :
    clientWidth(width),
    clientHeight(height)
{
#ifdef WIN32
	hWnd = NULL;
	hDC = NULL;

	HINSTANCE hInst     = ::GetModuleHandle(0);
    wc.cbSize        	= sizeof(WNDCLASSEX);
    wc.style         	= 0;
    wc.lpfnWndProc   	= FWApplication::GetMessageHandler();
    wc.cbClsExtra    	= 0;
    wc.cbWndExtra    	= 0;
    wc.hInstance     	= hInst;
    wc.hIcon         	= LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       	= LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground 	= (HBRUSH)GetStockObject(NULL_BRUSH);
    wc.lpszMenuName  	= TEXT("GenericAppMenu");
    wc.lpszClassName 	= TEXT("myWindowClass");
    wc.hIconSm       	= LoadIcon(NULL, IDI_APPLICATION);
	if(!RegisterClassEx(&wc))
    {
        throw "Window Registration Failed";
    }

    hWnd = ::CreateWindowEx(	
		WS_EX_CLIENTEDGE,									// Window Style
		TEXT("myWindowClass"),								// name of a registered window class
		TEXT("The title of my window"),						// window caption
		WS_OVERLAPPEDWINDOW,								// window style
		CW_USEDEFAULT,										// x position
		CW_USEDEFAULT,										// y position
		this->clientWidth,									// witdh
		this->clientHeight,									// height
		NULL,												// handle to parent window
		NULL,												// handle to menu
		hInst,	    										// application instance
		this);
	
    if(hWnd == NULL)
    {
        throw "Window Creation Failed";
        exit(1);
    }

    if (!oglDevice)
         oglDevice = new FWOpenGLDevice(this);

	if (!d3dDevice)
		d3dDevice = new FWD3DDevice(this);
#else
	xDisplay = NULL;
    xDisplay = FWApplication::GetMainDisplay();

    int errno, event;
    if (!glXQueryExtension(xDisplay, &errno, &event))
        throw "GLX Extension not supported";

    if (!oglDevice)
         oglDevice = new FWOpenGLDevice(this);

    xVisualInfo = oglDevice->GetDevice()->xVisualInfo;
    xColorMap = oglDevice->GetDevice()->xColorMap;

    xSetWindowAttributes.colormap = xColorMap;
    xSetWindowAttributes.border_pixel = 0;
    xSetWindowAttributes.event_mask = ExposureMask | KeyPressMask | ButtonPress |
            StructureNotifyMask | ButtonReleaseMask |
            KeyReleaseMask | EnterWindowMask | LeaveWindowMask |
            PointerMotionMask | Button1MotionMask | VisibilityChangeMask |
            ColormapChangeMask;

    xWindow = XCreateWindow(
                xDisplay,
                RootWindow(xDisplay, xVisualInfo->screen),
                0, 0,
                width, height,
                0,
                xVisualInfo->depth,
                InputOutput,
                xVisualInfo->visual,
                CWBorderPixel | CWColormap | CWEventMask | CWCursor | CWOverrideRedirect,
                &xSetWindowAttributes
                );

    XSetStandardProperties(
                           xDisplay,
                           xWindow,
                           "glxsimple",
                           "glxsimple",
                           None,
                           NULL,
                           0,
                           NULL
                          );

#endif
    FWApplication::RegisterMainWidget(this);
}

FWWindow::~FWWindow()
{
#ifdef WIN32
    ::DestroyWindow(hWnd);
    ::ReleaseDC(hWnd, hDC);
#elif __linux__
    if (linux_timer)
        delete linux_timer;
    if (call_back)
        delete call_back;
#endif
}

void FWWindow::Show()
{
#ifdef WIN32
	STARTUPINFO startupInfo;
	GetStartupInfo(&startupInfo);
	int cmdShow = (startupInfo.dwFlags & STARTF_USESHOWWINDOW) ? startupInfo.wShowWindow : SW_SHOWDEFAULT;
    this->hDC = ::GetDC(hWnd);
	::ShowWindow(hWnd, cmdShow);									
	::UpdateWindow(hWnd);
#elif __linux__
    XMapWindow(xDisplay, xWindow);
#endif
}

int FWWindow::getClientWidth()
{
  return this->clientWidth;
}

int FWWindow::getClientHeight()
{
  return this->clientHeight;
}

void FWWindow::AddTimer(unsigned long micro_seconds)
{
#ifdef WIN32
	static unsigned int timerID = 0;
	SetTimer(hWnd, timerID++, (int)(micro_seconds/ 1000), NULL);
#elif __linux__
    if (!linux_timer && !call_back)
    {
        call_back = new FWCallBack<FWWindow, int, unsigned int>(this, &FWWindow::TimerHandler);
        linux_timer = new FWLinuxTimer<FWWindow>();
        linux_timer->start();
    }
    if (linux_timer && call_back)
        linux_timer->addTimer(micro_seconds, call_back);
#endif
}

void FWWindow::ResizeHandler(int width, int height)
{
#ifdef WIN32
#elif __linux__
    if (height == 0)
        height =1;
    BeginDraw();
    if (oglDevice)
        oglDevice->Resize(width, height);
    EndDraw();
#endif
}

void FWWindow::BeginDraw()
{
#ifdef WIN32G
	if (d3dDevice)
	    d3dDevice->BeginScene();
#else
	if (oglDevice)
        oglDevice->BeginScene();
#endif
}

void FWWindow::EndDraw()
{
#ifdef WIN32G
	if (d3dDevice)
	    d3dDevice->PresentScene();
#else
	if (oglDevice)
        oglDevice->PresentScene();
#endif
}

#ifdef WIN32
HWND FWWindow::getHWND()
{
    return this->hWnd;
}

HDC  FWWindow::getHDC()
{
    this->hDC = ::GetDC(hWnd);
    return this->hDC;
}
#elif __linux__
Window *FWWindow::getWindow()
{
    return &xWindow;
}
#endif

void FWWindow::InputHandler(FWEvent */*event*/)
{
    fprintf(stderr, "I recieved an event");
}

int FWWindow::TimerHandler(unsigned int /*timer*/)
{
	return 0;
}

void FWWindow::Draw()
{
}

void FWWindow::ReDraw(int width, int height)
{
    Resize(width, height);
    Draw();
}

void FWWindow::CheckTimers()
{
#ifdef WIN32
#elif __linux__
    if (linux_timer)
            linux_timer->check_timers();
#endif
}

#include "FWApplication.h"
#include "FWMouseHandler.h"
#include "FWKeyboardHandler.h"
#include "FWWidget.h"

FWApplication *FWApplication::_instance = NULL;
bool FWApplication::_initialized = false;
FWWidget *FWApplication::_mainWidget = NULL;
FWMouseHandler *FWApplication::_mouseHandler = NULL;
FWKeyboardHandler *FWApplication::_keyboardHandler = NULL;

#ifdef __linux__
Display *FWApplication::_xDisplay = NULL;
#endif


FWApplication *FWApplication::Initialize()
{
    if (!_instance)
    {
#ifdef __linux__
        XInitThreads();
        _xDisplay = XOpenDisplay(NULL);
        if (_xDisplay == NULL)
            throw "Failed to get XDisplay";
#endif
        _initialized = true;
        _instance = new FWApplication();
		_mouseHandler = FWMouseHandler::Instance(_instance);
		_keyboardHandler = FWKeyboardHandler::Initialize(_instance);
	}
	return _instance;
}

void FWApplication::RegisterMainWidget(FWWidget *mainWidget)
{
    if (!_mainWidget)
        _mainWidget = mainWidget;
    else
        throw "Cannot have multiple Main Windows\n" \
              "Try adding other widgets to Main Window";
}

int FWApplication::Run()
{
    if (!_initialized)
		return -1;
#ifdef WIN32
	MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT) 
    {
        if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
	    {
	        ::TranslateMessage(&msg);
	        ::DispatchMessage(&msg);
	    } 
    }
#elif __linux__
    static bool run = true;
    static Display *lDisplay = _xDisplay;
    XEvent xEvent;
    while (run)
    {
        if (_mainWidget)
            _mainWidget->CheckTimers();
        while (XPending(GetMainDisplay()))
        {
            XNextEvent(lDisplay, &xEvent);
            switch (xEvent.type)
            {
            case Expose: {
                break;
            }
            case ConfigureNotify: {
                int width = xEvent.xconfigure.width;
                int height = xEvent.xconfigure.height;

                if (width != 0 && height != 0)
                    if (_mainWidget)
                        _mainWidget->Resize(width, height);
            }
            break;
            case VisibilityNotify:
                break;
            case DestroyNotify:
                break;
            case ButtonPress:
            case ButtonRelease:
            case EnterNotify:
            case MotionNotify:
            case LeaveNotify:
                if(_mouseHandler)
                    _mouseHandler->HandleInput(lDisplay, &xEvent);
                break;
            case KeyPress:
            case KeyRelease:
                if(_keyboardHandler)
                    _keyboardHandler->HandleInput(lDisplay, &xEvent);
                break;
            case ClientMessage:
                if (strcmp(XGetAtomName(
                           FWApplication::GetMainDisplay(),
                           xEvent.xclient.message_type),
                           "WM_PROTOCOLS") == 0)
                {
                    run = False;
                }
                break;
            default:
                break;
            }
        }
    }
#endif
    return EXIT_SUCCESS;
}

FWApplication::FWApplication()
{
}

FWApplication::~FWApplication()
{
#ifdef WIN32
#elif __linux__
    XCloseDisplay(_xDisplay);
#endif
}

#ifdef WIN32
typedef LRESULT (CALLBACK *MessageHandler)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
MessageHandler FWApplication::GetMessageHandler()
{
    return FWApplication::WndProc;
}

LRESULT CALLBACK FWApplication::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static FWWidget *wdgt;
	wdgt = (FWWidget*)::GetWindowLongPtr(hWnd, GWL_USERDATA);

	if(message == WM_NCCREATE)
	{
		wdgt = (FWWidget*)(((CREATESTRUCT*)lParam)->lpCreateParams);
		if (wdgt) 
            ::SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)wdgt);
		return ::DefWindowProc(hWnd, message, wParam, lParam);
	}
	switch (message)
	{
	case WM_TIMER :         // 0x0113
		wdgt->TimerHandler(wParam);
		break;
	case WM_SIZE :
		wdgt->Resize(LOWORD(lParam), HIWORD(lParam));
	case WM_MOUSEACTIVATE : // 0x0021
	case WM_MOUSEMOVE :     // 0x0200
	case WM_LBUTTONDOWN :   // 0x0201
	case WM_LBUTTONUP :     // 0x0202
	case WM_LBUTTONDBLCLK : // 0x0203
	case WM_RBUTTONDOWN :   // 0x0204
	case WM_RBUTTONUP :     // 0x0205
	case WM_RBUTTONDBLCLK : // 0x0206
	case WM_MBUTTONDOWN :   // 0x0207
	case WM_MBUTTONUP :     // 0x0208
	case WM_MBUTTONDBLCLK : // 0x0209 
	case WM_MOUSEWHEEL :    // 0x020A
	case WM_MOUSEHWHEEL :   // 0x020E
	case WM_MOUSELEAVE :    // 0x02A3
        if(_mouseHandler)
            _mouseHandler->HandleInput(hWnd, message, wParam, lParam);
		break;
	case WM_KEYDOWN:        // 0x0100
		switch (wParam)
		{
		case VK_LBUTTON :   // 0x0001 
		case VK_RBUTTON :   // 0x0002
		case VK_MBUTTON :   // 0x0003
            if(_mouseHandler)
                _mouseHandler->HandleInput(hWnd, message, wParam, lParam);
			break;
		default :
            if(_keyboardHandler)
                _keyboardHandler->HandleInput(hWnd, message, wParam, lParam);
		}
	    break;
	case WM_KEYUP:          // 0x0101
		switch (wParam)
		{
		case VK_LBUTTON :   // 0x0001 
		case VK_RBUTTON :   // 0x0002
		case VK_MBUTTON :   // 0x0003
            if(_mouseHandler)
                _mouseHandler->HandleInput(hWnd, message, wParam, lParam);
			break;
		default :
            if (_keyboardHandler)
                _keyboardHandler->HandleInput(hWnd, message, wParam, lParam);
		}
	    break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	default:
		return ::DefWindowProcA(hWnd, message, wParam, lParam);
	}
    return ::DefWindowProcA(hWnd, message, wParam, lParam);
}
#elif __linux__
Display *FWApplication::GetMainDisplay()
{
    if (_xDisplay)
        return _xDisplay ;
    else
        return NULL;
}

#endif

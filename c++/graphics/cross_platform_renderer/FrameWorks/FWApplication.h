#ifndef FWAPPLICATION_H_
#define FWAPPLICATION_H_

#ifdef WIN32
#include <WinMain.h>
#endif

#include "FWGlobals.h"
class FWWidget;
class FWMouseHandler;
class FWKeyboardHandler;

class FWApplication
{
protected:
    FWApplication();
    ~FWApplication();
#ifdef WIN32
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	typedef LRESULT (CALLBACK *MessageHandler)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
#endif
public:
    static FWApplication *Initialize();
    static void RegisterMainWidget(FWWidget *mainWidget);
    static int Run();
#ifdef __linux__
    static Display *GetMainDisplay();
#elif WIN32
    static MessageHandler GetMessageHandler();
#endif
private:
    static FWApplication *_instance;
    static bool _initialized;
    static FWWidget *_mainWidget;
	static FWMouseHandler *_mouseHandler;
    static FWKeyboardHandler *_keyboardHandler;

	friend class FWMouseHandler;
	friend class FWKeyboardHandler;
#ifdef __linux__
    static Display *_xDisplay;
#endif
};

#endif

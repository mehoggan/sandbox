#ifndef FWMOUSEHANDLER_H_
#define FWMOUSEHANDLER_H_

#include "FWGlobals.h"
class FWApplication;

class FWMouseHandler
{
public:
	static FWMouseHandler *Instance(FWApplication *app);
protected:
	FWMouseHandler(void);
	~FWMouseHandler(void);
private:
	static FWMouseHandler *_instance;
	static FWApplication *_appInstance;
#ifdef WIN32
	enum MOUSE_EVENTS
	{
	    MOUSEACTIVATE = 0x0021, MOUSEMOVE = 0x0200, LBUTTONDOWN = 0x0201, LBUTTONUP = 0x0202,
	    LBUTTONDBLCLK = 0x0203, RBUTTONDOWN = 0x0204, RBUTTONUP = 0x0205, RBUTTONDBLCLK = 0x0206,
	    MBUTTONDOWN = 0x0207, MBUTTONUP = 0x0208, MBUTTONDBLCLK = 0x0209, MOUSEWHEEL = 0x020A,
	    MOUSEHWHEEL = 0x020E, MOUSELEAVE = 0x02A3
	};
#endif
#ifdef WIN32
	void HandleInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
#elif __linux__
    void HandleInput(Display *display, XEvent *event);
#endif
	friend class FWApplication;
};

#endif


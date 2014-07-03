#ifndef FWWINDOW_H_
#define FWWINDOW_H_

#include "FWWidget.h"
class FWEvent;
class FWOpenGLDevice;

#ifdef WIN32
class FWD3DDevice;
#elif __linux__
template<class CallObject>
class FWLinuxTimer;
template <class Object, typename ReturnType, typename Parameter>
class FWCallBack;
#endif


class FWWindow : public FWWidget
{
public:
    FWWindow(void);
    FWWindow(int width, int height);
    virtual ~FWWindow();
    virtual void Show();
    virtual int getClientWidth();
    virtual int getClientHeight();
    virtual void AddTimer(unsigned long micro_seconds);
    virtual void ResizeHandler(int width, int height);
	void BeginDraw();
	void EndDraw();
protected:
	int clientWidth;
    int clientHeight;

	virtual void InputHandler(FWEvent *event);
    virtual int TimerHandler(unsigned int timer);
    virtual void Draw();
    virtual void ReDraw(int width, int height);
    virtual void CheckTimers();

    friend class FWApplication;
    friend class FWKeyboardHandler;
    friend class FWMouseHandler;
	friend class FWTimer;
    friend class FWOpenGLDevice;
	friend class FWD3DDevice;

#ifdef WIN32
    HWND getHWND();
    HDC  getHDC();
#elif __linux__
    virtual Window *getWindow();
#endif

	static FWOpenGLDevice *oglDevice;
#ifdef WIN32
	static FWD3DDevice *d3dDevice;
#elif __linux__
#endif
    
#ifdef WIN32
#elif __linux__
    static FWCallBack<FWWindow, int, unsigned int> *call_back;
    static FWLinuxTimer<FWWindow> *linux_timer;
#endif
private:
#ifdef WIN32
    HWND hWnd;
    HDC hDC;
    WNDCLASSEX wc;										
#elif __linux__
    Display *xDisplay;
    XVisualInfo *xVisualInfo;
    Colormap xColorMap;
    Window xWindow;
    XSetWindowAttributes xSetWindowAttributes;
    int xScreen;
    int xDepth;
#endif
};
#endif	//	WINMAKER

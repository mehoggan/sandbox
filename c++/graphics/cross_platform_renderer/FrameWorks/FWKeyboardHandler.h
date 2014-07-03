#ifndef FWKEYBOARDHANDLER_H_
#define FWKEYBOARDHANDLER_H_

#include "FWGlobals.h"
class FWApplication;
	
class FWKeyboardHandler
{
public:
	static FWKeyboardHandler *Initialize(FWApplication *app);
protected:
	FWKeyboardHandler(void);
	~FWKeyboardHandler(void);
private:
	static FWKeyboardHandler *_instance;
	static FWApplication *_appInstance;
	friend class FWApplication;
#ifdef WIN32
	void HandleInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
#elif __linux__
    void HandleInput(Display *display, XEvent *event);
#endif

#ifdef WIN32
    enum FWSYSTEM_KEYS 
    {
    };
    enum FWNORMAL_KEYS
    {
	    ZER0 = 0x30, ONE = 0x31, TWO = 0x32, THREE = 0x33, FOUR = 0x34, FIVE = 0x35, SIX = 0x36, 
	    SEVEN = 0x37, EIGHT = 0x38, NINE = 0x39 ,
	    A = 0x41, B = 0x42, C = 0x43, D = 0x44, E = 0x45, F = 0x46, G = 0x47, H = 0x48, I = 0x49, 
	    J = 0x4A, K = 0x4B, L = 0x4C, M = 0x4D, N = 0x4E, O = 0x4F, P = 0x50, Q = 0x51, R = 0x52, 
	    S = 0x53, T = 0x54, U = 0x55, V = 0x56, W = 0x57, X = 0x58, Y = 0x59, Z = 0x5A, MULT = 0x6A,
	    ADD = 0x6B, SEPARATOR = 0x6C, DECIMAL = 0x6E, DIVIDE = 0x6F
    };
#elif __linux__
    enum FWSYSTEM_KEYS
    {
            BACKSPACE = 0xFF08, TAB = 0xFF09,
            ENTER = 0xff0d,
            SHIFT = 0xffe1, CTRL = 0xffe3, ALT = 0xffe8, PAUSE = 0xff13, CAPSLOCK = 0xffe5,
            ESCAPE = 0xff1b,
            SPACE = 0xff80, PAGEUP = 0xff55, PAGEDOWN = 0xff56, 
    }
#endif
};

#endif

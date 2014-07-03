#ifndef FWWIDGET_H_
#define FWWIDGET_H_

#include "FWApplication.h"
class FWEvent;

class FWWidget
{
public:
    FWWidget(void);
    virtual ~FWWidget(void) = 0;	
    virtual void AddTimer(unsigned long micro_seconds) = 0;
#ifdef WIN32
#elif __linux__
    virtual Window *getWindow() = 0;
#endif
protected:
	virtual void InputHandler(FWEvent *event) = 0;
    virtual int TimerHandler(unsigned int timer) = 0;
    virtual void Resize(int width, int height) = 0;
    virtual void Draw() = 0;
    virtual void ReDraw(int width, int height) = 0;
    virtual void CheckTimers() = 0;
private:
	friend class FWApplication;
	friend class FWKeyboardHandler;
	friend class FWMouseHandler;
    friend class FWTimer;
};

#endif


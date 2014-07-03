#ifndef MAPWINDOW_H_
#define MAPWINDOW_H_

#include "FWWindow.h"
class FWEvent;
class MapGL;

class MapWindow :  public FWWindow
{
public:
    MapWindow(int width, int height);
    virtual void InputHandler(FWEvent *event);
    virtual int TimerHandler(unsigned int timer);
    virtual void Draw();
    virtual void ReDraw(int width, int height);
    virtual void Resize(int width, int height);
private:
    bool resize;
    double rotate;
    float theta;
};

#endif

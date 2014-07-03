#include "FWMouseHandler.h"
#include "FWWidget.h"
#include "FWEvent.h"

FWMouseHandler *FWMouseHandler::_instance = NULL;
FWApplication *FWMouseHandler::_appInstance = NULL;

FWMouseHandler *FWMouseHandler::Instance(FWApplication *app)
{
	if (!_instance)
	{
		_appInstance = app;
		_instance = new FWMouseHandler;
		return _instance;
	}

	// Only application will have access
	return NULL;
}

FWMouseHandler::FWMouseHandler(void)
{
}


FWMouseHandler::~FWMouseHandler(void)
{
}

#ifdef WIN32
void FWMouseHandler::HandleInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    FWEvent *event = new FWEvent();
	if (_appInstance && _appInstance->_mainWidget)
		_appInstance->_mainWidget->InputHandler(event);
	if(event)
	    delete event;
}
#elif __linux__
void FWMouseHandler::HandleInput(Display */*display*/, XEvent *event)
{
    FWEvent *fwEvent = new FWEvent();
    if (_appInstance && _appInstance->_mainWidget)
        _appInstance->_mainWidget->InputHandler(fwEvent);
    if(event)
        delete fwEvent;
}
#endif

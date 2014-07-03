#include "FWKeyboardHandler.h"
#include "FWWidget.h"
#include "FWEvent.h"

FWKeyboardHandler *FWKeyboardHandler::_instance = NULL;
FWApplication *FWKeyboardHandler::_appInstance = NULL;

FWKeyboardHandler *FWKeyboardHandler::Initialize(FWApplication *app)
{
	if (!_instance)
	{
		_appInstance = app;
		_instance = new FWKeyboardHandler;
		return _instance;
	}

	// Only application will have access
	return NULL;
}

FWKeyboardHandler::FWKeyboardHandler(void)
{
}

FWKeyboardHandler::~FWKeyboardHandler(void)
{
}

#ifdef WIN32
void FWKeyboardHandler::HandleInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
        // TODO -- Add in input to FWEvent
	FWEvent *event = new FWEvent();
	if (_appInstance && _appInstance->_mainWidget)
		_appInstance->_mainWidget->InputHandler(event);
	if(event)
	    delete event;
}
#elif __linux__
void FWKeyboardHandler::HandleInput(Display */*display*/, XEvent *event)
{
    // TODO -- Add in input to FWEvent
    FWEvent *fwEvent = new FWEvent();
    if (_appInstance && _appInstance->_mainWidget)
        _appInstance->_mainWidget->InputHandler(fwEvent);
    if(event)
        delete fwEvent;
}
#endif

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <Windows.h>
#include "IApplication.h"
#include "IWindow.h"
#include "IController.h"
#include "Controller.h"

namespace nApplication
{
	class Application : public IApplication
	{
	public:
		Application( HINSTANCE hInstance, int nCmdShow );
		virtual ~Application( );
		virtual int Run( );
		virtual int getnCmdShow( ) { return mnCmdShow; }
		virtual HINSTANCE gethInstance( ) { return mhInstance; }
		virtual IController* getMainControl( ) { return main_control; }
	private:
		int mnCmdShow;
		HINSTANCE mhInstance;
		int MessageLoop();
		Application( Application &app );
		Application& operator= ( const Application &app );
	};

}

#endif /* IAPPLICATION */
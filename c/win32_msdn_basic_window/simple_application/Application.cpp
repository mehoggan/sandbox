#include "Application.h"
#include "MainWindow.h"

namespace nApplication
{
	Application::Application( HINSTANCE hInstance, int nCmdShow )
		: mhInstance( hInstance ), mnCmdShow( nCmdShow )
	{
	}

	Application::~Application( )
	{
	}


	int Application::Run( )
	{
		main_window = new MainWindow( this );
		main_control = new Controller( this );
		main_window->Init( );
		main_window->Display( );
		MessageLoop( );
		delete main_window;
		return 0;
	}

	int Application::MessageLoop()
    {
	    MSG msg;

	    while(GetMessage(&msg, NULL, 0, 0) != 0) 
	    {
		    TranslateMessage(&msg);
		    DispatchMessage(&msg);
	    }
	    return (int)msg.wParam;
    }
}
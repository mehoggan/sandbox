#ifndef IAPPLICATION_H_
#define IAPPLICATION_H_

#include <Windows.h>

namespace nApplication
{
	class IController;
    class IWindow;

	class IApplication
	{
	public:
		virtual int Run( ) = 0;
		virtual HINSTANCE gethInstance( ) = 0;
		virtual int getnCmdShow( ) = 0;
		virtual IController* getMainControl( ) = 0;
	protected:
		IWindow *main_window;
		IController *main_control;
	private:
		virtual int MessageLoop() = 0;
	};
}

#endif /* IAPPLICATION */
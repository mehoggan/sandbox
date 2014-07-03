#include <windows.h>
#include "Application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	nApplication::Application app( hInstance, nCmdShow );
	return app.Run( );
}

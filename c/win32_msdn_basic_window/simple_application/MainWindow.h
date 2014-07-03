#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <windows.h>
#include "IWindow.h"
#include "IController.h"
#include "IApplication.h"

namespace nApplication
{
    class MainWindow : public IWindow
    {
    public:
        MainWindow( IApplication *iApp);
	    ~MainWindow();
	    void Init();
	    void Display( );
    private:
        WNDCLASSEX wc;
	    HWND hWnd;
	    IApplication *iApp;
    };
}

#endif //MAINWINDOW_H_
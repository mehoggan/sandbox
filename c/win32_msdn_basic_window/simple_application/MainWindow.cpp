#include "MainWindow.h"

namespace nApplication
{
	namespace 
	{
	    LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            HDC hDC;
	        PAINTSTRUCT ps;

	        static IController *cntrl;
	        cntrl = (IController*)::GetWindowLongPtr(hWnd, GWL_USERDATA);

     	    if(uMsg == WM_NCCREATE)
	        {
	            cntrl = (IController*)(((CREATESTRUCT*)lParam)->lpCreateParams);
                ::SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)cntrl);
		        cntrl->CheckStatus();
                return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	        }

	        switch(uMsg) 
	        {
	            case WM_CREATE:
		        {
		        }
		        case WM_PAINT:
		        {			 
       		        hDC = BeginPaint( hWnd, &ps );
	    	        TextOut( hDC, 10, 10, TEXT("Hello, Windows!"), 15 );
		            EndPaint( hWnd, &ps );
			        return 0;
		        }
		        case WM_DESTROY:
		        {
   		            PostQuitMessage( 0 );
	                return 0;
		        }
		        default:
		        {
    			    return DefWindowProc( hWnd, uMsg, wParam, lParam );
	    	    }
            }
	    }
	}

    MainWindow::MainWindow( IApplication* iApp ) : iApp( iApp )
    {
	    wc.cbSize        = sizeof(WNDCLASSEX);
        wc.style         = 0;
        wc.lpfnWndProc   = MainWndProc;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = iApp->gethInstance( );
        wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
        wc.lpszMenuName  = TEXT( "GenericAppMenu");
        wc.lpszClassName = TEXT( "myWindowClass" );
        wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
    }

    MainWindow::~MainWindow()
    {
    }

    void MainWindow::Init()
    {
	    if( !RegisterClassEx(&wc) )
        {
            MessageBox(NULL, TEXT( "Window Registration Failed!" ), TEXT( "Error!" ), MB_ICONEXCLAMATION | MB_OK);
            exit(0);
        }
    }

    void MainWindow::Display( )
    {
	    hWnd = ::CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("myWindowClass"), 
		TEXT("The title of my window"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 
		240, 120, NULL, NULL, iApp->gethInstance( ), iApp->getMainControl( ) );

        if(hWnd == NULL)
        {
            ::MessageBox( NULL, TEXT( "Window Creation Failed!" ), 
			    TEXT( "Error!" ), MB_ICONEXCLAMATION | MB_OK );
            exit(0);
        }

		::ShowWindow( hWnd, iApp->getnCmdShow( ) );
        ::UpdateWindow(hWnd);
    }
}
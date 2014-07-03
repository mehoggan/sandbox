#ifndef MAINWNDPROC_H_
#define MAINWNDPROC_H_

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;

	switch( uMsg ) 
	{
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
			return DefWindowProc( hWnd, uMsg, wParam, lParam );
	}
}

#endif //MAINWNDPROC_H_
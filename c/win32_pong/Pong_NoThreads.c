/*
 *  Basic Drawing By Matthew Hoggan
 *  Using Simple GDI Functions
 *  November 08 2009
 *  I don't know what this program is going to do
 */

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#define TRUE        1


RECT     rect;
POINT    rect1[4] = {0, 0, 0, 0, 0, 0, 0, 0};
POINT    rect2[4] = {0, 0, 0, 0, 0, 0, 0, 0};
POINT    ball[4] = {0, 0, 0, 0, 0, 0, 0, 0};

void Update_Rect(POINT cord[4], int Xlt, int Ylt, int Xlb, int Ylb, int Xrt, int Yrt, int Xrb, int Yrb)
{
    cord[0].x = Xlt;
    cord[0].y = Ylt;
    cord[1].x = Xlb;
    cord[1].y = Ylb;
    cord[2].x = Xrt;
    cord[2].y = Yrt;
    cord[3].x = Xrb;
    cord[3].y = Yrb;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int         mdl_top;
    int         mdl_lft;
    HDC         hdc;
    PAINTSTRUCT ps;
    HBRUSH      hBrush;
    RECT corners1;
    RECT corners2;

    switch (message)
    {
        case WM_CREATE:
        {
            GetClientRect(hwnd, &rect);
            mdl_top = (int)(((rect.bottom + rect.top)/2) - 50);
            mdl_lft = (int)(((rect.left + rect.right)/2));
            Update_Rect(rect1, 0, mdl_top, 0, (mdl_top + 100), 20, (mdl_top + 100), 20, mdl_top);
            Update_Rect(rect2, (rect.right - 20), mdl_top, (rect.right - 20), (mdl_top + 100), rect.right, (mdl_top + 100), rect.right, mdl_top);
            return 0 ;
        }
        case WM_PAINT:
        {
            hdc = BeginPaint(hwnd, &ps);
            hBrush = GetStockObject(WHITE_BRUSH);
            SelectObject(hdc, hBrush);
            Polygon(hdc, rect1, 4);
            Polygon(hdc, rect2, 4);
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_CHAR:
        {

            switch((TCHAR) wParam)
            {
                case 'w':
                {
                    if(rect1[0].y == 0)
                    {
                    }
                    else
                    {
                        corners1.left = 0;
                        corners1.right = 20;
                        corners1.top = rect1[0].y;
                        corners1.bottom = rect1[1].y;
                        InvalidateRect(hwnd, &corners1, TRUE);
                        Update_Rect(rect1, 0, (rect1[0].y - 1), 0, (rect1[1].y - 1), 20, (rect1[2].y - 1), 20, (rect1[3].y - 1));
                        UpdateWindow(hwnd);
                    }
                    return 0;
                }
                case's':
                {
                    if(rect1[1].y == rect.bottom)
                    {
                    }
                    else
                    {
                        corners1.left = 0;
                        corners1.right = 20;
                        corners1.top = rect1[0].y;
                        corners1.bottom = rect1[1].y;
                        InvalidateRect(hwnd, &corners1, TRUE);
                        Update_Rect(rect1, 0, (rect1[0].y + 1), 0, (rect1[1].y + 1), 20, (rect1[2].y + 1), 20, (rect1[3].y + 1));
                        UpdateWindow(hwnd);
                    }
                    return 0;
                }
                case'o':
                {
                    if(rect2[0].y == 0)
                    {
                    }
                    else
                    {
                        corners2.left = rect.right - 20;
                        corners2.right = rect.right;
                        corners2.top = rect2[0].y;
                        corners2.bottom = rect2[1].y;
                        InvalidateRect(hwnd, &corners2, TRUE);
                        Update_Rect(rect2, (rect.right - 20), (rect2[0].y - 1), (rect.right - 20), (rect2[1].y - 1), rect.right, (rect2[2].y - 1), rect.right, (rect2[3].y - 1));
                        UpdateWindow(hwnd);
                    }
                    return 0;
                }
                case 'l':
                {
                    if(rect2[1].y == rect.bottom)
                    {
                    }
                    else
                    {
                        corners2.left = rect.right - 20;
                        corners2.right = rect.right;
                        corners2.top = rect2[0].y;
                        corners2.bottom = rect2[1].y;
                        InvalidateRect(hwnd, &corners2, TRUE);
                        Update_Rect(rect2, (rect.right - 20), (rect2[0].y + 1), (rect.right - 20), (rect2[1].y + 1), rect.right, (rect2[2].y + 1), rect.right, (rect2[3].y + 1));
                        UpdateWindow(hwnd);
                    }
                    return 0;
                }
            }

            return 0;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0 ;
        }
    }
    return DefWindowProc(hwnd, message, wParam, lParam) ;
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szClassName[] = TEXT ("basic");
    HWND            h_MainWindow;
    MSG             msg ;
    WNDCLASSEX      wc ;
    RECT            rect;
    int             mdl_top;
    int             mdl_lft;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    h_MainWindow = CreateWindow (szClassName, TEXT("First Project"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    ShowWindow (h_MainWindow, iCmdShow);
    UpdateWindow (h_MainWindow);

    while (GetMessage (&msg, NULL, 0, 0))
    {
         TranslateMessage (&msg);
         DispatchMessage (&msg);
    }
    return msg.wParam ;
}

#ifndef WINMAIN_H_
#define WINMAIN_H_

#include <Windows.h>
#include <Windowsx.h>

// WinMain will call a main function that you must define
extern int main(int argc, char *argv[]);

// Entry point into a windows application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

#endif
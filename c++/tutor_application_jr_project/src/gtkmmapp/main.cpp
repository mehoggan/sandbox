//============================================================================
// Name        : main.cpp
// Author      : Matthew Hoggan
// Version     :
// Copyright   : This is free software
// Description : Tutor_Application Fall 2009
//============================================================================

#include "MainWindow.h"

int main(int argc, char* argv[])
{
	if(!Glib::thread_supported())
	{
		Glib::thread_init();
		cout << "Threads initialized " << endl;
	}
	Main kit(argc, argv);
	MainWindow* window = new MainWindow(WINDOW_TOPLEVEL);
	kit.run(*(window));
	return 0;
}

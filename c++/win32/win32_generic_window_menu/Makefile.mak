main.exe : main.cpp 
	rc Generic.rc
	cl /EHs main.cpp MainWindow.cpp IController.cpp MainController.cpp Generic.res kernel32.lib user32.lib gdi32.lib
main.exe : main.cpp 
	cl /EHsc main.cpp Application.cpp Controller.cpp MainWindow.cpp user32.lib gdi32.lib
	del *.obj
#/link /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup
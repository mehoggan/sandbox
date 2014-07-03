main.exe : main.cpp DXWindow.cpp
	cl /EHs main.cpp DXWindow.cpp kernel32.lib user32.lib gdi32.lib
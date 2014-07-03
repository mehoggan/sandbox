SOURCES=main.cpp WinMaker.cpp ControllerGL.cpp
LIBS=user32.lib gdi32.lib kernel32.lib opengl32.lib glu32.lib
COMPILER=cl.exe
LINK=link.exe
FLAGS=/EHs
DELETE=del

main.exe:$(SOURCES)
	$(COMPILER) $(FLAGS) $(SOURCES) $(LIBS)
	$(DELETE) *.obj
	
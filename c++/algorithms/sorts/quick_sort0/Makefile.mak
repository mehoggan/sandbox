SOURCES = QuickSort.cpp

EXEC = QuickSort.exe

CPPFLAGS = /EHs

COMPILER = cl.exe

$(EXEC) : $(SOURCES)
	$(COMPILER) $(CPPFLAGS) $(SOURCES) $(LIBS)

	

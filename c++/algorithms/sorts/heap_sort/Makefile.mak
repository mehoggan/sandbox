SOURCES = InsertionSort.cpp

EXEC = InsertionSort.exe

CPPFLAGS = /EHs

COMPILER = cl.exe

$(EXEC) : $(SOURCES)
	$(COMPILER) $(CPPFLAGS) $(SOURCES) $(LIBS)

	

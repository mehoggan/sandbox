SOURCES = MergeSort.cpp

EXEC = MergeSort.exe

CPPFLAGS = /EHs

COMPILER = cl.exe

$(EXEC) : $(SOURCES)
	$(COMPILER) $(CPPFLAGS) $(SOURCES) $(LIBS)

	

#
# This will be the program name
#
PROGRAM = main.exe

#
# Include directories
#
INCLUDEDIRS = /I "C:\Program Files\Microsoft Visual Studio 10.0\VC\include"

#
# The CPPSOURCES macro contains a list of source files.
#
CPPSOURCES = main.cpp 

#
# The CPPOBJECTS macro contains a list of object files.
#
CPPOBJECTS = main.obj

#
# The LIBDIRS macro contsins the path to the lib directory
#
LIBDIRS = "C:\Program Files\Microsoft Visual Studio 10.0\VC\lib"

#
# The LIBS macro is the basic libs needed to compile windows 
# program
#
LIBS = 

#
# The RESOURCES macro is the for all resource files
#
RESOURCES = 

#
# These are the compiler flags
#
CPPFLAGS = /EHsc $(INCLUDEDIRS)

$(PROGRAM) : $(CPPSOURCES) $(CPPLIBS)
#	rc.exe $(RESOURCES)
	cl.exe $(CPPFLAGS) $(CPPSOURCES) $(LIBS)
	link.exe $(CPPOBJECTS) $(LIBS)
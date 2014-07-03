#
# Visual Studio Version
#
VERSION = 10.0

#
# This will be the program name
#
PROGRAM = TorriApp.exe

#
# Include directories
#
INCLUDEDIRS = /I "C:\Program Files\Microsoft Visual Studio $(VERSION)\VC\include"

#
# The CPPSOURCES macro contains a list of source files.
#
CPPSOURCES = main.cpp ship.cpp skybox.cpp torpedo.cpp torus.cpp explosion.cpp

#
# The CPPOBJECTS macro contains a list of object files.
#
CPPOBJECTS = main.obj ship.obj skybox.obj torpedo.obj torus.obj explosion.obj

#
# The LIBDIRS macro contsins the path to the lib directory
#
LIBDIRS = "C:\Program Files\Microsoft Visual Studio $(VERSION)\VC\lib"

#
# The LIBS macro is the basic libs needed to compile windows 
# program
#
LIBS = kernel32.lib user32.lib GDI32.lib $(LIBDIRS)\glut32.lib

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
#	link.exe $(CPPOBJECTS) $(LIBS)
	
#
# This will be the program name
#
PROGRAM = DXVertices.exe

#
# Include directories
#
INCLUDEDIRS = /I "C:\Program Files\Microsoft DirectX SDK (February 2010)\Include"

#
# The CPPSOURCES macro contains a list of source files.
#
CPPSOURCES = Vertices.cpp

#
# The CPPOBJECTS macro contains a list of object files.
#
CPPOBJECTS = Vertices.obj

#
# The LIBDIRS macro contsins the path to the lib directory
#
LIBDIRS = "C:\Program Files\Microsoft DirectX SDK (February 2010)\Lib\x86"

#
# The LIBS macro is the basic libs needed to compile windows program
#
LIBS = kernel32.lib user32.lib GDI32.lib $(LIBDIRS)\*.lib

#
# The RESOURCES macro is the for all resource files
#
RESOURCES = Vertices.rc

#
# These are the compiler flags
#
CPPFLAGS = /EHsc $(INCLUDEDIRS)

$(PROGRAM) : $(CPPSOURCES) $(CPPLIBS)
	rc.exe $(RESOURCES)
	cl.exe $(CPPFLAGS) $(CPPSOURCES) $(LIBS)
	link.exe $(CPPOBJECTS) $(LIBS)
	
lib_LTLIBRARIES = libgl_wrapper_system.la

AM_CPPFLAGS = -I$(top_srcdir)/..
ACLOCAL_AMFLAGS = -I m4

# List your sources
libgl_wrapper_system_la_SOURCES = \
	concurrency/exceptions/concurrency_exception.cpp \
	concurrency/mutex/posix/mutex.cpp

# List version info and other linker flags.
libgl_wrapper_system_la_LDFLAGS = -version-info 1:0:0 -pthread

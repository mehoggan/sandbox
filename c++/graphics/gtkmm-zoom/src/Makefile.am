bin_PROGRAMS = sampleapplication

# List your sources
sampleapplication_SOURCES = main.cpp examplewindow.cpp drawingarea.cpp pngfilereader.cpp ../include/drawingarea.h ../include/examplewindow.h ../include/pngfilereader.h

sampleapplication_LDADD = $(DEPS_LIBS) $(GTKMM_LIBS) $(libpng_LIBS)
AM_CXXFLAGS = $(GTKMM_CFLAGS) 
AM_CPPFLAGS = -I$(top_srcdir)/include -DUSE_LIBPNG

#if DEBUG
#AM_CXXFLAGS += -g3 -O0
#else
#AM_CXXFLAGS += -O2
#endif

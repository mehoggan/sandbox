libapue_LTLIBRARIES = libapue-1.0.la
libapue_LIBRARIES = libapue-1.0.a
libapuedir = $(libdir)/lib/apue
libapue_1_0_la_SOURCES = error.c  error_daemon.c max_number_of_open_files.c  path_length_allocator.c  set_clear_file_status_flags.c
libapue_1_0_a_SOURCES = error.c  error_daemon.c max_number_of_open_files.c  path_length_allocator.c  set_clear_file_status_flags.c
libapue_includedir = $(includedir)/apue/apue.h
libapue_include_HEADERS = ../../include/apue.h
libapue_1_0_la_CPPFLAGS = -I ../../include
libapue_1_0_la_LDFLAGS = -shared
libapue_1_0_a_CPPFLAGS = -I ../../include

all-local: libapue-1.0.a
	cp libapue-1.0.a ./.libs

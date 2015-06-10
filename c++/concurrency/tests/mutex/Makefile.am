bin_PROGRAMS = unit_test_system_concurrency_mutex

AM_CPPFLAGS = "-I$(top_srcdir)/../../../../../"
AM_CPPFLAGS += "-I$(top_srcdir)/../../../../cxxtest-4.2.1/"
ACLOCAL_AMFLAGS = -I m4

AM_LDFLAGS = -L$(prefix)/lib -lgl_wrapper_system

CXXTEST = ../../../../cxxtest-4.2.1/bin/cxxtestgen.py

CLEANFILES = runner.cpp runner.o

runner.cpp :
	$(CXXTEST) --error-printer -o runner.cpp $(top_srcdir)/mutex.h

install-exec-local :
	$(prefix)/bin/unit_test_system_concurrency_mutex && cat results.txt && \
	valgrind --xml=yes --xml-file=valgrind.xml --leak-check=full \
		--show-reachable=yes --error-exitcode=1 \
		$(prefix)/bin/unit_test_system_concurrency_mutex

# List your sources
unit_test_system_concurrency_mutex_SOURCES = \
	runner.cpp

TESTS = check_binary_balanced
check_PROGRAMS = check_binary_balanced

check_binary_balanced_SOURCES = \
	check_rb_tree.c \
	rb_tree.h

check_binary_balanced_CFLAGS = @CHECK_CFLAGS@

check_binary_balanced_LDADD = \
	$(top_builddir)/src/libbinary_balanced.la \
	@CHECK_LIBS@ \
	-lm \
	-lrt

check_binary_balanced_LDFLAGS = \
  -pthread

@VALGRIND_CHECK_RULES@

CLEANFILES = *.o
CLEANDIRS = deps/ \
	.lib/

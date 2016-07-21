#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([binary_balanced], [0.1], [mehoggan@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_CONFIG_SRCDIR([./src/])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_PROG_CC
AM_PROG_AR
AM_PATH_CHECK

LT_INIT

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AX_VALGRIND_DFLT()
AX_VALGRIND_CHECK

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 tests/Makefile])
AC_OUTPUT

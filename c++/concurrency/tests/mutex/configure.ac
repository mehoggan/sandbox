#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([unit_test_system_concurrency_mutex], [0.1], [mehoggan@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
m4_pattern_allow([AM_PROG_AR])
AM_PROG_AR
LT_INIT([shared] [static])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([./])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Dependent make files
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

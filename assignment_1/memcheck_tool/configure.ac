#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(["memcheck_tool"], 1.0)
AC_CONFIG_SRCDIR([lib/libmemcheck.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE
# Checks for programs.
AC_PROG_CC
AC_PROG_CPP
# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_ENABLE_SHARED
AC_DISABLE_STATIC
AC_PROG_LIBTOOL(libtool)
LDFLAGS = "-ldl"
# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([putenv])

AC_CONFIG_FILES([Makefile
                 lib/Makefile
                 src/Makefile])
AC_OUTPUT

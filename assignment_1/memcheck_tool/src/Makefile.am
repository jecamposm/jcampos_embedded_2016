AM_CFLAGS = -I$(top_srcdir)/src

bin_PROGRAMS = memcheck 
memcheck_SOURCES = memcheck.c
memcheck_CFLAGS = "-DLD_OVERRIDE="$(top_srcdir)/lib/.libs/libmemcheck.so

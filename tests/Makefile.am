
AM_CPPFLAGS = -I $(top_srcdir)/include
AM_CFLAGS = -g
AM_LDFLAGS = -pthread
LDADD = $(top_builddir)/src/.libs/libsocketpp.a
check_PROGRAMS = basic_server
basic_server_SOURCES = basic_server.cc

TESTS = $(check_PROGRAMS)

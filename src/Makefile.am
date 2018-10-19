
# src/Makefile.am

AM_CPPFLAGS = -I$(top_srcdir)/include # $(DEPS_CFLAGS)
AM_CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2
AM_LDFLAGS  = -version-number 1:0:0

lib_LTLIBRARIES = libsocketpp.la

libsocketpp_la_SOURCES = baseserver.cc \
                         basesockbuf.cc \
                         baseaddr.cc \
                         basesocket.cc \
                         inetaddr.cc \
			 unixaddr.cc
# libsocketpp_la_LIBADD = $(DEPS_LIBS)

install-exec-hook:
	@(cd $(DESTDIR)$(libdir) && $(RM) $(lib_LTLIBRARIES))

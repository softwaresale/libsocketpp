
# src/Makefile.am

AM_CPPFLAGS = -I$(top_srcdir)/include
AM_CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2
AM_LDFLAGS  = -version-number 0:0:0

lib_LTLIBRARIES = libsocketpp.la

libsocketpp_la_SOURCES = baseserver.cc \
                         basesockbuf.cc \
                         baseaddr.cc \
                         basesocket.cc \
                         inetaddr.cc

install-exec-hook:
	@(cd $(DESTDIR)$(libdir) && $(RM) $(lib_LTLIBRARIES))

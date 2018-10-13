
# src/Makefile.am

AM_CPPFLAGS = -I$(top_srcdir)/include/
AM_CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2
AM_LDFLAGS  = -version-number 1:0:0

lib_LTLIBRARIES = libsocketpp.la

libsocketpp_la_SOURCES = basesocket.cc \
			 basesockbuf.cc \
			 tcpsocket.cc \
			 tcpserver.cc

install-exec-hook:
	@(cd $(DESTDIR)$(libdir) && $(RM) $(lib_LTLIBRARIES))

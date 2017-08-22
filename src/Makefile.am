
AM_CPPFLAGS = -I../include/
AM_CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
AM_LDFLAGS = -version-number 0:1:1 -lcrypt -lpthread

lib_LTLIBRARIES = libsocketpp.la

libsocketpp_la_SOURCES = server.cc basesocket.cc basesockbuf.cc socket.cc

install-exec-hook:
	@(cd $(DESTDIR)$(libdir) && $(RM) $(lib_LTLIBRARIES))

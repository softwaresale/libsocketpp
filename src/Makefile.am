
AM_CPPFLAGS = -I../include/
AM_CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
AM_LDFLAGS = -version-number 0:1:0

lib_LTLIBRARIES = libsocketpp.la

libsocketpp_la_SOURCES = server.cc \
			 basesocket.cc \
			 basesockbuf.cc \
			 socket.cc \
			 httpbase.cc \
			 httprequest.cc \
			 httpresponse.cc

install-exec-hook:
	@(cd $(DESTDIR)$(libdir) && $(RM) $(lib_LTLIBRARIES))

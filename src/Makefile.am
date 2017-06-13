
AM_CPPFLAGS = -I../include/
AM_LDFLAGS = -version-number 2:1:0

LIIBTOOL_DEPS = @LIIBTOOL_DEPS@

libtool: $(LIIBTOOL_DEPS)
	$(SHELL) ./config.status libtool

lib_LTLIBRARIES = libsocketpp.la

libsocketpp_la_SOURCES = basesocket.cc basesockbuf.cc server.cc socket.cc basesockstream.cc

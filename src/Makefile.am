
AM_CPPFLAGS = -I../include/
AM_CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
AM_LDFLAGS = -version-number 0:1:1

lib_LTLIBRARIES = libsocketpp.la

libsocketpp_la_SOURCES = server.cc basesocket.cc basesockbuf.cc socket.cc
libsocketpp_la_LDADD = crypt


all: client server

server: lib/libsocketpp.a server.cc
	g++ server.cc lib/libsocketpp.a -I./include --std=c++11 -g -o server

client: lib/libsocketpp.a client.cc
	g++ client.cc lib/libsocketpp.a -I./include --std=c++11 -g -o client

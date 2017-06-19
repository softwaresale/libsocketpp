
all: client server

client: client.cc lib/libsocketpp.a
	g++ client.cc lib/libsocketpp.a -g -I./include -o client --std=c++11

server: server.cc lib/libsocketpp.a
	g++ server.cc lib/libsocketpp.a -g -I./include -o server --std=c++11

clean:
	rm client server

remake: clean all

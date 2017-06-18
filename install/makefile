
all: client server

client: client.cc lib/libsocketpp.a
	g++ client.cc lib/libsocketpp.a -g -I./include -o client

server: server.cc lib/libsocketpp.a
	g++ server.cc lib/libsocketpp.a -g -I./include -o server

clean:
	rm client server

remake: clean all

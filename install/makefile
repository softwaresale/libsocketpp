
all: server client

server: server.cc lib/libsocketpp.a
	g++ server.cc lib/libsocketpp.a -g -I./include -o server

client: client.cc lib/libsocketpp.a
	g++ client.cc lib/libsocketpp.a -g -I./include -o client

clean:
	rm client server

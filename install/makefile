
all: server client

server: server.cc
	g++ $< lib/libsocketpp.a -I./include -o $@

client: client.cc
	g++ $< lib/libsocketpp.a -I./include -o $@

clean:
	rm server client

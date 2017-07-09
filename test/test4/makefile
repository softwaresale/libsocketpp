LIB = ../lib/libsocketpp.a
INC = ../include/

all: server client

server: server.cc $(LIB)
	g++ --std=c++11 -I$(INC) -g server.cc $(LIB) -o $@

client: client.cc $(LIB)
	g++ --std=c++11 -I$(INC) -g client.cc $(LIB) -o $@

clean:
	rm client server

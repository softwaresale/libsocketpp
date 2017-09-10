LIB = ../lib/libsocketpp.a 
INC = ../include/

all: test

test: test.cc $(LIB)
	g++ -std=c++17 -I$(INC) -g test.cc $(LIB) -o $@

server: server.cc $(LIB)
	g++ --std=c++17 -I$(INC) -g server.cc $(LIB) -o $@

client: client.cc $(LIB)
	g++ --std=c++17 -I$(INC) -g client.cc $(LIB) -o $@

clean:
	rm client server

CC=g++
CFLAGS=-fPIC -c -std=c++11
LFLAGS=-shared -Wl,-soname,libsocketpp.so.1 -o libsocketpp.so.1.0
SRC=$(wildcard src/*.cpp)
OBJ=$(wildcard out/*.o)

all: $(OBJ)
	$(CC) $(LFLAGS) $^
	mv *.so* out/

src: $(SRC)
	$(CC) $(CFLAGS) $^
	mv *.o out/

install:
	sudo cp header/tcp/* /usr/local/include/socketpp/tcp/
	sudo cp out/*.so* /usr/local/lib
	sudo ldconfig

clean:
	rm out/*

test: servertest.cpp clienttest.cpp
	$(CC) servertest.cpp -o server -l socketpp
	$(CC) clienttest.cpp -o client -l socketpp

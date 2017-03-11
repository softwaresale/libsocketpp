CC=g++
CFLAGS=-fPIC -c -std=c++11
LFLAGS=-shared -Wl,-soname,libsocketpp.so.1 -o out/libsocketpp.so.1.0
SRC=$(wildcard src/*.cpp)
OBJ=$(SRC:.cpp=.o)

INSTALL_PATH=/usr/local
LIB1=libsocketpp.so.1.0
LIB2=libsocketpp.so.1
LIB3=libsocketpp.so

all: $(OBJ)
	$(CC) $(LFLAGS) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

install: all
	sudo cp out/libsocketpp.so.1.0 $(INSTALL_PATH)/lib
	sudo ln -sf $(INSTALL_PATH)/lib/$(LIB1) $(INSTALL_PATH)/lib/$(LIB2)
	sudo ln -sf $(INSTALL_PATH)/lib/$(LIB2) $(INSTALL_PATH)/lib/$(LIB3)
	sudo cp -r header/* /usr/local/include/socketpp/
	sudo ld-config

clean:
	rm $(OBJ)

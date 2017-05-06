
CC=g++
CFLAGS=-fPIC -c -std=c++11
LFLAGS=-shared -Wl,-soname,libsocketpp.so.1 -o out/libsocketpp.so.1.0
SRC=$(wildcard src/*.cc)
OBJ=$(SRC:.cc=.o)

INSTALL_PATH=/usr/local
LIB1=libsocketpp.so.1.0
LIB2=libsocketpp.so.1
LIB3=libsocketpp.so

all: $(OBJ)
	$(CC) $(LFLAGS) $(OBJ)

%.o: %.cc
	$(CC) $(CFLAGS) $< -o $@

install: all
	sudo cp out/libsocketpp.so.1.0 $(INSTALL_PATH)/lib
	sudo ln -sf $(INSTALL_PATH)/lib/$(LIB1) $(INSTALL_PATH)/lib/$(LIB2)
	sudo ln -sf $(INSTALL_PATH)/lib/$(LIB2) $(INSTALL_PATH)/lib/$(LIB3)
	sudo cp -r include/* /usr/local/include/socketpp/
	sudo ldconfig

clean:
	rm src/*.o 

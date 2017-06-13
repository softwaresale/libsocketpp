#include "include/socketpp/tcp/socket.h"
#include "include/socketpp/tcp/server.h"
#include "include/socketpp/tcp/basesockbuf.h"
#include <iostream>

using namespace std;
using namespace tcp;

int main()
{
	/*
	cout << "Creating server..." << endl;
	Server serv = Server(8888);
	cout << "Server created..." << endl;
	cout << "Binding..." << endl;
	serv.binds();
	cout << "Bound" << endl;
	
	cout << "Waiting..." << endl;
	Socket sock = serv.accepts();
	cout << "Conn found" << endl;
	
	// test accessing socket function	
	if (!sock.isConnected()){
		
		cout << "Socket connected" << endl;
		
		cout << "Reading data..." << endl;
		// read a char from the socket
		char ch = sock.get();
	
		cout << "Data: " << ch << endl; // output the char
		
		// closing socket
		sock.closes(); // close the socket
		
	} else {
		cerr << "Socket not connected" << endl;
	}
	
	serv.closes();
	*/
	
	Server serv(8888);
	serv.binds();
	
	int fd = serv.acceptfd();
	Basic_Sockbuf buf(fd);
	
	iostream io(&buf);
	
	if (!buf.isConnected()){
		cerr << "Error" << endl;
		return 1;
	}
	
	char ch = io.get();
	cout << ch << endl;
	
	io.put('a');
	
	return 0;
}

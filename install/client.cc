#include "include/socketpp/tcp/socket.h"
#include "include/socketpp/tcp/basesockbuf.h"
#include <iostream>

using namespace std;
using namespace tcp;

int main()
{
	///*
	cout << "Creating socket..." << endl;
	Socket sock = Socket("192.168.1.98", 8888); // local connection
	cout << "Created"     << endl;
	
	// test Basic_socket member
	if (!sock.isConnected()){
		
		// test iostream func
		sock.put('c'); // write 'c' to socket
		
		cout << sock.getLocalhost() << endl; // test basic_sockstream
		
		sock.closes();      // another 
		
	} else {
		cerr << "Socket not connected" << endl;
	}
	//*/
	/*
	Basic_Sockbuf* sockbuf = new Basic_Sockbuf("192.168.1.98", 8888);
	iostream io(sockbuf);
	
	if (sockbuf->isConnected()){
		
		io.put('c');
		char ch = io.get();
		
		cout << ch << endl;
		
	} else {
		cerr << "Error" << endl;
	}
	*/
	
	return 0;
}

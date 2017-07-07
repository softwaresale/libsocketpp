#include <iostream>
#include <socketpp/tcp/socket.h>
#include <cstring>

using namespace std;
using namespace tcp;

int main()
{

	Socket sock("192.168.1.98", 8899);
	sock.connects();

	if (!sock.isConnected()){
		cerr << "Ack" << endl;
		return -1;
	}

	const char* msg = "Hello World";

	cout << "String length: " << strlen(msg) << endl;
	
	sock << msg << flush;

	sock.closes();
	
	return 0;
}

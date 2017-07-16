
#include <socketpp/tcp/socket.h>
#include <iostream>
#include <cstring>

using namespace std;
using namespace tcp;

int main()
{

	Socket sock;
	sock.connects("127.0.0.1", 8889);
	
	if (!sock.isConnected()){
		cerr << "Socket not connected" << endl;
		return -1;
	}
	
	const char* msg1 = "Hello World";
	const char* msg2 = "Hello World again";
	char* buffer = new char[256];
	
	sock << msg1 << endl;
	sock << msg2 << endl;
	
	sock.getline(buffer, 256);
	
	cout << "BUFFER: " << buffer << endl;
	
	sock.closes();

	return 0;
}

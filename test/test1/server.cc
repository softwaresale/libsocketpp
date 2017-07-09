#include <iostream>
#include <socketpp/tcp/server.h>
#include <socketpp/tcp/socket.h>
#include <cstring>

using namespace std;
using namespace tcp;

int main()
{	
	Server serv;
	serv.binds(8889);

	Socket& sock = serv.accepts();

	if (!sock.isConnected()){
		cerr << "Socket not isConnected" << endl;
		return -1;
	}
	
	char *msg1, *msg2 = new char[256];
	const char* msg = "Hello to you client";

	sock.getline(msg1, 256);
	sock.getline(msg2, 256);
	
	cout << "MSG1: " << msg1 << endl << "MSG2: " << msg2 << endl;

	sock << msg << endl;
	
	sock.closes();
	serv.closes();	

	return 0;
}

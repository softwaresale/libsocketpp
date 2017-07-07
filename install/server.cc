#include <iostream>
#include <socketpp/tcp/socket.h>
#include <socketpp/tcp/server.h>
#include <cstring>

using namespace std;
using namespace tcp;

int main(int argc, char** argv)
{

	Server serv(8899);
	serv.binds();
	Socket* sock = serv.accepts();
	
	/*
	if (!sock->isConnected()){
		cerr << "Ack" << endl;
		return -1;
	}
	*/

	char* buffer = new char[16];
	
	sock->get(buffer, 11);
	
	cout << buffer << endl;
	
	sock->closes();
	
	return 0;
}









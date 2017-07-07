#include <iostream>
#include <socketpp/tcp/socket.h>
#include <cstring>

using namespace std;
using namespace tcp;

int main()
{

	Socket sock("192.168.1.98", 8889);
	sock.connects();

	if (!sock.isConnected()){
		cerr << "Ack" << endl;
		return -1;
	}

	char* buffer = new char[12];
	
	sock.getline(buffer, 12);
	
	cout << "MSG RECV: " << buffer << endl << "MSG LEN: " << strlen(buffer) << endl;

	sock.closes();
	
	return 0;
}

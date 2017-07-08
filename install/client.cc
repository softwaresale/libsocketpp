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

	char* buffer = new char[256];
	
	char ch;
	int i;
	
	sock.get(buffer, 256);
	
	cout << "MSG RECV: " << buffer << endl << "MSG LEN: " << sock.gcount() << endl;
	
	sock.closes();
	
	return 0;
}

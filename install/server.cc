#include <iostream>
#include <cstring>
#include <socketpp/tcp/socket.h>
#include <socketpp/tcp/server.h>

using namespace std;
using namespace tcp;

int main()
{
	
	Server serv(8899);
	
	int ret = serv.binds();
	cout << "serv.binds() == " << ret << endl;
	
	Socket* sock = serv.accepts();
	if (!sock->isConnected()) /* not connected */ {
		cerr << "server: Socket is not connected" << endl;
		delete sock;
		serv.closes();
		return -1;
	} else {
		cout << "server: Socket is connected" << endl;
	}
	
	// Read data
	char* buffer = new char[32];
	sock->read(buffer, sizeof(buffer));
	
	cout << "Buffer: " << buffer << endl;
	
	sock->closes();
	
	serv.closes();
	
	return 0;
}

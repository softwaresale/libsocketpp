#include <socketpp/tcp/socket.h>
#include <socketpp/tcp/server.h>
#include <iostream>
#include <cstring>

using namespace std;
using namespace tcp;

int main()
{
	Server serv(8888);
	serv.binds();
	
	Socket* sock = serv.accepts();
	
	char* buffer = new char[23];
	
	sock->read(buffer, 23);
	
	cout << buffer << endl;
	
	delete sock;
	
	serv.closes();
	
	return 0;
}

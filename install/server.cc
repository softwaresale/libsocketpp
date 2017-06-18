#include <iostream>
#include <cstring>
#include <socketpp/tcp/socket.h>
#include <socketpp/tcp/server.h>

using namespace std;
using namespace tcp;

int main()
{
	
	Server serv(8899);
	serv.binds();
	
	Socket* sock = serv.accepts();
	if (sock->isConnected()){
		
		sock->sync();	
			
		char ch = sock->get();
		cout << ch << endl;
		
		sock->put('A');
		
		sock->closes();
		
	} else {
		cerr << "server: Socket not connected" << endl;
	}
	
	delete sock;
	
	serv.closes();
	
	return 0;
}

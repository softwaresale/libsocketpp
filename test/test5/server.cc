#include <iostream>
#include <socketpp/tcp/socket.h>
#include <socketpp/tcp/server.h>
#include <cstring>

using namespace std;
using namespace tcp;

int main(int argc, char** argv)
{
	Server serv(8888);
	serv.binds();
	Socket& sock = serv.accepts();
	
	// code here
	
	const char* localHost = sock.getLocalhost();
	
	char* remoteHost;
	remoteHost = sock.getPeerName();
	
	cout << "LOCALHOST: " << localHost << endl;
	cout << "REMOTEHOST: " << remoteHost << endl;
	
	sock.closes();
	serv.closes();
	return 0;
}

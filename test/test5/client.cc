#include <iostream>
#include <socketpp/tcp/socket.h>
#include <cstring>
#include <sys/socket.h>

using namespace std;
using namespace tcp;

int main(int argc, char** argv)
{
	Socket sock("192.168.1.98", 8888);
	sock.connects();
	
	// code here
	char* remotehost = sock.getPeerName();
	const char* localhost = sock.getLocalhost();
	
	cout << "LOCALHOST: " << localhost << endl;
	cout << "REMOTEHOST: " << remotehost << endl;

	sock.closes();
	return 0;
}

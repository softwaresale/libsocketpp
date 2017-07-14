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
	const char* localPassword = "password";
	const char* remotePassword = "otherpassword";
	char* readbuf = new char[64];

	
	
	sock.closes();
	serv.closes();
	return 0;
}

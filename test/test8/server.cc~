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
	
	sock.closes();
	serv.closes();
	return 0;
}

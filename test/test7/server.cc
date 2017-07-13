#include <iostream>
#include <socketpp/tcp/socket.h>
#include <socketpp/tcp/server.h>
#include <cstring>
#include <netinet/tcp.h>

using namespace std;
using namespace tcp;

int main(int argc, char** argv)
{
	Server serv(8888);
	serv.binds();
	Socket& sock = serv.accepts();

	char* value = new char[16];
	// code here
	sock.getOpt(SOL_SOCKET, TCP_MD5SIG, (void*) value);

	cout << "MD5 HASH VALUE: " << value << endl;
	
	sock.closes();
	serv.closes();
	return 0;
}

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
	
	int recvval;
	int sendval = 4;
	
	sock >> recvval;
	sock << sendval << endl;
	
	cout << "RECVVAL: " << recvval << endl;
	
	sock.closes();
	serv.closes();
	return 0;
}

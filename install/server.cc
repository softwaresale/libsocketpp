#include <iostream>
#include <socketpp/tcp/socket.h>
#include <socketpp/tcp/server.h>
#include <cstring>

using namespace std;
using namespace tcp;

int main(int argc, char** argv)
{
	Server serv(8899);
	
	serv.binds();
	Socket& sock = serv.accepts();
	
	
	if (!sock.isConnected()){
		cerr << "Ack" << endl;
		return -1;
	}
	
	int ret = sock.setOpt(SOL_SOCKET, SO_DEBUG, (const void*) 1); // should set debug option
	if (!ret){
		cerr << "Error encountered with setOpt" << endl;
		serv.closes();
		return -1;
	}
	
	const char* msg = "Hello World";
	
	sock << msg << endl;
	
	cout << "MSG: " << msg << endl << "MSG LEN: " << strlen(msg) << endl;
	
	serv.closes();
	
	return 0;
}









#include <iostream>
#include <socketpp/tcp/socket.h>
#include <socketpp/tcp/server.h>
#include <cstring>

using namespace std;
using namespace tcp;

int main(int argc, char** argv)
{

	Server serv(8889);
	
	serv.binds();
	Socket& sock = serv.accepts();
	
	
	if (!sock.isConnected()){
		cerr << "Ack" << endl;
		return -1;
	}
	

	const char* msg = "Hello World";
	
	sock.write(msg, strlen(msg));
	sock.flush();
	
	cout << "MSG: " << msg << endl << "MSG LEN: " << strlen(msg) << endl;
	
	sock.closes();
	
	return 0;
}









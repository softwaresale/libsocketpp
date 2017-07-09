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
	
	char* buf = new char[256];
	char* obuf = new char[256];
	
	cout << "Reading first data..." << endl;	
	sock.read(buf, 11);
	buf[strlen(buf)] = '\0';
	cout << "FIRST BUFFER: " << buf << endl;
	
	sock.read(obuf, 256);
	buf[strlen(buf)] = '\0';
	cout << "SECOND BUFFER: " << obuf << endl;
	
	const char* msg = "Hello Client";
	sock << msg << endl;
	
	sock.closes();
	serv.closes();
	return 0;
}

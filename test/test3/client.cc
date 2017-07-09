#include <iostream>
#include <socketpp/tcp/socket.h>
#include <cstring>

using namespace std;
using namespace tcp;

int main(int argc, char** argv)
{
	Socket sock("192.168.1.98", 8888);
	sock.connects();
	
	// code here
	
	const char* msg = "Hello World";
	const char* omsg = "Whats poppin";
	
	// send data
	sock << msg << endl;
	sock << omsg << endl;
	
	// read data
	char* buf = new char[256];
	
	sock.read(buf, 256);
	buf[strlen(buf)] = '\0';
	
	cout << buf << endl;

	sock.closes();
	return 0;
}

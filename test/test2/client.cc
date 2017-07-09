#include <iostream>
#include <socketpp/tcp/socket.h>
#include <cstring>

using namespace std;
using namespace tcp;

int main(int argc, char** argv)
{
	Socket sock("192.168.1.98", 8888);
	sock.connects();
	
	// sends characters
	
	// individual
	sock.put('a');
	sock.flush();
	
	sock.put('b');
	sock.flush();
	
	// send strings
	const char* msg1 = "Hello World\n";
	const char* msg2 = "Hello \r World\n";
	
	sock.write(msg1, strlen(msg1));
	sock.flush();
	
	// send string with delimeter
	sock.write(msg2, strlen(msg2));
	sock.flush();
	
	sock.closes();

	return 0;
}

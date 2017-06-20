#include <socketpp/tcp/socket.h>
#include <iostream>
#include <cstring>

using namespace std;
using namespace tcp;

int main()
{
	Socket sock("192.168.1.98", 8888);
	sock.connects();
	
	const char* msg = "HELLO WORLD. What is up";
	
	// size of msg
	cout << "String size: " << strlen(msg) << endl;
	
	sock << msg;

	sock.flush();
	
	sock.closes();

	return 0;
}

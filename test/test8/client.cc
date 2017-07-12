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

	sock.closes();
	return 0;
}

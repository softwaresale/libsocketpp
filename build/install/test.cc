
#include "include/socketpp/tcp/socket.h"
#include "include/socketpp/tcp/basesockstream.h"
#include "include/socketpp/tcp/basesocket.h"
#include "include/socketpp/tcp/basesockbuf.h"
#include <iostream>

using namespace std;
using namespace tcp;

int main()
{

	Socket sock("192.168.1.90", 8888);
	sock.connects();

	sock << "Hello World";

	sock.closes();

	return 0;
}

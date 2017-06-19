#include <socketpp/tcp/socket.h>
#include <iostream>
#include <cstring>

using namespace std;
using namespace tcp;

int main()
{
	Socket sock("127.0.0.1", 8899); // create a sock obj
	int ret = sock.connects();
	cout << "sock.connects() == " << ret << endl;
	
	if (!sock.isConnected()){
		cerr << "client: Socket is not connected" << endl;
		sock.closes();
		return -1;
	} 
	
	cout << "Client is connected." << endl;
	
	cout << "Writing data" << endl;
	
	const char* msg = "Hello World";
	
	sock.write(msg, strlen(msg));
	sock.flush();
	
	sock.closes();
	
	return 0;
}

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
	
	int sendval = 3;
	int recvval;

	sock << sendval << endl;
	
	sock >> recvval;
	
	cout << "READVALUE: " << recvval << endl;
	
	sock.closes();
	return 0;
}

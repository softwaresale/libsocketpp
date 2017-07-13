#include <iostream>
#include <socketpp/tcp/socket.h>
#include <cstring>
#include <netinet/tcp.h>

using namespace std;
using namespace tcp;

int main(int argc, char** argv)
{
	Socket sock("127.0.0.1", 8888);
	sock.connects();

	// code here

      	char* value = new char[16];
	// code here
	int ret = sock.getOpt(SOL_SOCKET, TCP_MD5SIG, (char*) value);
	if(ret == -1){
		cerr << "Error getting option" << endl;
		sock.closes();
		return 0;
	}

	cout << "MD5 HASH VALUE: " << value << endl;

	
	sock.closes();
	return 0;
}

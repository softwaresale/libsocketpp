#include <iostream>
#include <socketpp/tcp/socket.h>
#include <cstring>

using namespace std;
using namespace tcp;

int main(int argc, char** argv)
{
	Socket sock;
	int ret = sock.connects("www.google.com", 80);
	if (ret != 0){
		cerr << "Error encountered" << endl;	
	}
	
	// code here
	
	const char* req = "GET / HTTP/1.1\r\n\r\n";
	
	cout << "Sending..." << endl;	
	sock << req << endl;
	cout << "Sent" << endl;

	char* response = new char[256];

	sock.get(response, 256);

	cout << "RESPONSE: " << endl << response << endl;

	sock.closes();
	return 0;
}

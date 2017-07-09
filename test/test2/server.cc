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
	
	char ch;
	
	ch = sock.get();
	cout << "RETURN CHAR: " << ch << endl;
	
	sock.get(ch);
	cout << "PARAM CHAR: " << ch << endl;
	
	char* string = new char[256];
	
	sock.get(string, 256);
	cout << "GET STRING: " << string << endl;
	
	delete string;
	string = new char[256];
	
	sock.get(string, 256, '\r');
	cout << "DELIMINATOR STRING: " << string << endl;
	
	delete string;
	
	sock.closes();
	serv.closes();
	
	return 0;
}

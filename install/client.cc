#include <socketpp/tcp/socket.h>
#include <iostream>
#include <cstring>

using namespace std;
using namespace tcp;

int main()
{
	Socket sock("192.168.1.98", 8899);
	int ret = sock.connects(); // connects to host
	cout << "client: sock.connects() ret == " << ret << endl;
	
	if (!sock.isConnected()){
		cerr << "client: Socket not connected" << endl;
		return -1;
	} else {
		cout << "client: Socket connected" << endl;
	}
	
	// write data
	char ch = 'A';
	sock.put(ch);
	sock.sync();
	cout << "Getting value" << endl;
	char c = sock.get();
	if (c == '\377'){
		cout << "EOF" << endl;
		sock.closes();
		return 1;
	}
		
	cout << c << endl;
	
	sock.closes();
	
	return 0;
}

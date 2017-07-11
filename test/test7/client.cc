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
	ofstream out("client_out_test.txt", ios::out);
	if (!out.is_open()){
		cout << "of not open" << endl;
		return -1;
	}

	ifstream in("client_in_test.txt", ios::in);
	if (!in.is_open()){
		cout << "if not open" << endl;
	}

	sock >> out;
	sock << in << endl;

	sock.closes();
	return 0;
}

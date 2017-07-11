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

	// code here
	ofstream out("server_out_test.txt", ios::out);
	if (!out.is_open()){
		cout << "of not open" << endl;
		return -1;
	}

	ifstream in("server_in_test.txt", ios::in);
	if (!in.is_open()){
		cout << "if not open" << endl;
	}

	sock << in << endl;
	sock >> out;

	sock.closes();
	serv.closes();
	return 0;
}

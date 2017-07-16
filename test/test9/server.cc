#include <iostream>
#include <socketpp/tcp/socket.h>
#include <socketpp/tcp/server.h>
#include <cstring>
#include <errno.h>

using namespace std;
using namespace tcp;

int main(int argc, char** argv)
{
	Server serv(8888);
	int ret;
	ret = serv.setKeepAlive();
	if (ret == -1){
		cerr << "Error setting keep alive" << endl;
		serv.closes();
		switch(errno){
		case EBADF:
			cerr << "Invalid fd" << endl;
			break;
		case EDOM:
			cerr << "Timeout" << endl;
			break;
		case EINVAL:
			cerr << "Invalid option" << endl;
			break;
		default:
			cerr << "Default" << endl;
			break;
		}
		return -1;
	}

	ret = serv.setReuseAddr();
	if (ret == -1){
		cerr << "Error setting reuse addr" << endl;
		serv.closes();
		return -1;
	}

	int boo = serv.isKeepAlive();
	if (boo == -1){
		cerr << "Error getting iskeepalive" << endl;
		serv.closes();
		return -1;
	}

	int boo2 = serv.isReuseAddr();
	if (boo2 == -1){
		cerr << "Error getting reuse" << endl;
		serv.closes();
		return -1;
	}

	if (boo2 && boo){
		cout << "Success in getting values" << endl;
	} else {
		cout << "Failed getting values." << endl;
		cout << "BOO: " << boo << endl << "BOO2: " << boo2 << endl;
	}

	serv.binds();

	// code here

	Socket& sock = serv.accepts();

	sock.closes();
	serv.closes();
	return 0;
}
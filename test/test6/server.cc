#include <iostream>
#include <socketpp/tcp/socket.h>
#include <socketpp/tcp/server.h>
#include <cstring>
#include <iomanip>

using namespace std;
using namespace tcp;

int main(int argc, char** argv)
{
	Server serv(8888);
	serv.binds();
	Socket& sock = serv.accepts();
	
	// code here
	
	double val = 2.3;
	
	sock << val << endl;
	
	double oval;
	
	sock >> oval;
	
	cout << "DOUBLE: " << oval << endl;
	
	float fval = 5.6;
	float ofval;
	
	sock << fval << endl;
	sock >> ofval;

	cout << "FLOAT: " << fixed << setprecision(5) << ofval << endl;
	
	sock.closes();
	serv.closes();
	return 0;
}

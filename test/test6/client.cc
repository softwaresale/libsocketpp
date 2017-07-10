#include <iostream>
#include <socketpp/tcp/socket.h>
#include <cstring>
#include <iomanip>

using namespace std;
using namespace tcp;

int main(int argc, char** argv)
{
	Socket sock("192.168.1.98", 8888);
	sock.connects();
	
	// code here
	
	double val;
	sock >> val;
	
	double oval = 4.5;

	sock << oval << endl;
	
	cout << "DOUBLE: " << val << endl;
	
	float ofval;
	float fval = 7.8009;
	
	sock >> ofval;
	sock << fval << endl;

	cout << "FLOAT: " << fixed << setprecision(8) << ofval << endl;

	sock.closes();
	return 0;
}

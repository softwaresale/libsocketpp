
#ifndef SOCKET_H
#define SOCKET_H 1

#include <socketpp/tcp/basesocket.h>
#include <iostream>
#include <socketpp/tcp/basesockbuf.h>

using namespace std;

namespace tcp
{

class Socket : public tcp::basic_socket, public iostream
{

private:

protected:

public:
	Socket(const char*, int);
	Socket(int);
	
};
		
};

#endif // SOCKET_H

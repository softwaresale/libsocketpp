
#ifndef SOCKET_H
#define SOCKET_H 1

#include <socketpp/tcp/basesocket.h>
#include <socketpp/tcp/basereadbuf.h>
#include <socketpp/tcp/basewritebuf.h>
#include <socketpp/tcp/basesockin.h>
#include <socketpp/tcp/basesockout.h>
#include <istream>
#include <ostream>

using namespace std;

namespace tcp
{

class Socket : public tcp::basic_socket, public ostream, public istream
{

private:

protected:

public:
	Socket(const char* host, int port);
	Socket(int sockfd);
	
};
		
};

#endif // SOCKET_H

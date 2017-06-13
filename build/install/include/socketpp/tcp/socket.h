
/* The final product */

#ifndef SOCKET_H
#define SOCKET_H 1

#include <tcp/basesockbuf.h>
#include <tcp/basesocket.h>
#include <tcp/basesockstream.h>
#include <ostream>

using namespace std;

namespace tcp
{

class Socket : public tcp::Basic_Sockstream
{

private:

protected:

public:
	Socket();
	Socket(char* host, int port);
	Socket(int sockfd);
};

};

#endif // SOCKET_H

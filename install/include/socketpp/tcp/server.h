#ifndef SERVER_PP
#define SERVER_PP

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "socket.h"

using namespace std;

/* Server class: wrapper for C sockets, specifically server */

/* namespace tcp */
namespace tcp {

class Server {

protected:
	int                server, conn;
	struct sockaddr_in addr;
	int                port;
	bool              _isBound = false;

public:
	Server();                        // creates a server without address data
	Server(int _port);               // creates a server and binds address

	int binds();                     // binds the server to the address if data is already given
	int binds(int _port);            // binds address with data
	
	bool isBound();                  // true if server is bound, false if not

	tcp::Socket* accepts();           // accepts a socket connection and returns a socket
	int          acceptfd();          // returns the connected socket descriptor

	void closes();                   // closes the server

};

}
#endif
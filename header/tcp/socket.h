#ifndef SOCKET_PP
#define SOCKET_PP 1

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

using namespace std;

/* Socket class: a class wrapper for TCP/IP sockets in C */

/* Dealing with TCP sockets */
namespace tcp {

class Socket {

protected:
	int                socketfd;
	struct sockaddr_in addr;
	char*              host;
	int                port;

public:
	Socket();                           // create a socket that does not have address info defined
	Socket(char* host, int port);       // create a new socket class with host and port
	Socket(int sockd);                  // create a socket class from existing socket descriptor

	int connects(char* host, int port); // connects to the server if address is not set
	int connects();                     // connects to the server if address already set

	int sends(char* buffer);            // sends a string
	int sends(int ii);                   // sends an integer

	char* reads();                      // reads the socket and returns a string
	int   readint();                    // reads an integer

	void closes();                      // closes the connection

};

}

#endif

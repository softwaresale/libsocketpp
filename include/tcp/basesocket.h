#ifndef SOCKET_PP
#define SOCKET_PP 1

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <streambuf>

using namespace std;

/* Socket class: a class wrapper for TCP/IP sockets in C */

/* Dealing with TCP sockets */
namespace tcp {

class Basic_socket
{

protected:
	int                socketfd;
	struct sockaddr_in addr;
	char*              host;
	int                port;
	bool              _isConnected;

public:
	Basic_socket();                           // create a socket that does not have address info defined
	Basic_socket(char* host, int port);       // create a new socket class with host and port
	Basic_socket(int sockd);                  // create a socket class from existing socket descriptor
	
	int getSockfd();                    // returns the socket descriptor
	// char* getLocalhost();               // gets the localhost of the socket

	int connects(char* host, int port); // connects to the server if address is not set
	int connects();                     // connects to the server if address already set

	bool isConnected();                 // true if the socket is connected

	void closes();                      // closes the connection

};

}

#endif

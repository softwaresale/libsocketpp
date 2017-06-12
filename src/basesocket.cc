#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include "../include/tcp/basesocket.h"

using namespace std;

/* Basic socket */

tcp::Basic_socket::Basic_socket()
{

	socketfd = socket(AF_INET, SOCK_STREAM, 0); // creates the new socket
	if (socketfd < 0){
		cerr << "Error creating socket" << endl;
		return;
	}
	
	_isConnected = false;
}

tcp::Basic_socket::Basic_socket(char* _host, int _port)
{

	host = _host; // sets the class host variable
	port = _port; // sets the class port variable


	socketfd = socket(AF_INET, SOCK_STREAM, 0); // creates the new socket
	if (socketfd < 0){
		cerr << "Error creating socket" << endl;
		return;
	}
	
	_isConnected = false;
}

tcp::Basic_socket::Basic_socket(int sockd)
{
	_isConnected = true; // socket should be connected
	socketfd = sockd; // sets the socket descriptor
}

int
tcp::Basic_socket::getSockfd()
{
	return this->socketfd;
}

bool
tcp::Basic_socket::isConnected()
{
	return _isConnected;
}

int
tcp::Basic_socket::connects(char* _host, int _port)
{

	addr.sin_family      = AF_INET;         // sets the address's family
	addr.sin_port        = htons(_port);     // sets the address's port
	addr.sin_addr.s_addr = inet_addr(_host); // sets the address's host

	if ( connect(socketfd, (struct sockaddr*)&addr, sizeof(addr)) < 0){
		cerr << "Error connecting to server" << endl;
		return 1;
	}

	_isConnected = true;
	return 0;
}

int
tcp::Basic_socket::connects()
{

	if (host == NULL || port == 0){

		cerr << "Error: host or port not set. Use 'connect(host, port)' instead" << endl;
		return 1;

	}

	addr.sin_family      = AF_INET;          // sets the address's family
	addr.sin_port        = htons(port);      // sets the address's port
	addr.sin_addr.s_addr = inet_addr(host);  // sets the address's host

	if ( connect(socketfd, (struct sockaddr*)&addr, sizeof(addr)) < 0){
		cerr << "Error connecting to host" << endl;
		return 1;
	}
	
	_isConnected = true;

	return 0;
}

void
tcp::Basic_socket::closes()
{
	close(socketfd);
}

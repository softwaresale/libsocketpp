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
#include "../include/socketpp/tcp/basesocket.h"

using namespace std;

/* Basic socket */

/*
tcp::Basic_socket::Basic_socket()
{

	socketfd = socket(AF_INET, SOCK_STREAM, 0); // creates the new socket
	if (socketfd < 0){
		cerr << "Error creating socket" << endl;
		return;
	}
	
	_isConnected = false;
}
*/

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
/*
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
*/

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

char*
tcp::Basic_socket::getLocalhost()
{
	
	struct sockaddr_in localAddress;
	socklen_t addressLen = sizeof(localAddress);

	getsockname(socketfd, (struct sockaddr*)&localAddress, &addressLen);

	char* addr = inet_ntoa(localAddress.sin_addr);

	return addr; // get the local address
}

int
tcp::Basic_socket::sends(char* buffer)
{

	int bytes;

	/* First, send the size of buffer */
	int datalen = strlen(buffer); // get sizeof buffer
	int len     = htonl(datalen); // reformat

	bytes = send(socketfd, (char*)&len, sizeof(len), 0); // send the size
	if (bytes < 0){
		cerr << "Error sending size of buffer to socket" << endl;
		return -1;
	}

	/* Now acutally send the data */

	bytes = send(socketfd, buffer, datalen, 0);
	if (bytes < 0){
		cerr << "Error writing buffer to socket" << endl;
		return -1;
	}
	
	cout << bytes << " written" << endl;

	return 0;

}

int
tcp::Basic_socket::sendc(char ch)
{
	int bytes;

	bytes = send(socketfd, (char*)&ch, sizeof(ch), 0); // send a character
	if (bytes < 0){
		cerr << "Error sending data" << endl;
		return -1;
	}

	return 0;
}

/*

int
tcp::Basic_socket::sends(int ii)
{

	int bytes;

	char* in = (char*)&ii;

	//* First, send the size of buffer 
	int datalen = strlen(in);     // get sizeof buffer
	int len     = htonl(datalen); // reformat

	bytes = send(socketfd, (char*)&len, sizeof(len), 0); // send the size
	if (bytes < 0){
		cerr << "Error sending size of buffer to socket" << endl;
		return 1;
	}

	/* Now acutally send the data 

	bytes = send(socketfd, in, datalen, 0);
	if (bytes < 0){
		cerr << "Error writing buffer to socket" << endl;
		return 1;
	}

	return 0;
}
*/

/*
char*
tcp::Basic_socket::reads()
{

	char* buffer;
	int bytes, buflen;

	/* Read the incoming size 
	bytes = recv(socketfd, (char*)&buflen, sizeof(buflen), 0);
	if (bytes < 0){
		cerr << "Error reading size of data" << endl;
		return NULL;
	}
	buflen = ntohl(buflen);

	buffer = new char[buflen+1]; // create a buffer for reading with room for null terminator

	/* Read the data 

	bytes = recv(socketfd, buffer, buflen, 0);
	if (bytes < 0){
		cerr << "Error reading data" << endl;
		return NULL;
	}

	buffer[buflen] = '\0'; // set the null terminator

	return buffer;
}

*/

void
tcp::Basic_socket::readc(char* buffer, int size)
{
	int bytes;
	bytes = recv(socketfd, buffer, size, 0);
	if (bytes < 0){
		cerr << "Error reading data" << endl;
		return -1;
	}

	return ch;
}

void
tcp::Basic_socket::closes()
{
	close(socketfd);
}

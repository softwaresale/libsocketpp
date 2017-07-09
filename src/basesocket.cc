
/*
  This is the base class that contains the basic connection
  protocols and functions for sending and recieving data  

    Copyright (C) 2017  Charlie Sale

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


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
#include <errno.h> // THINK ABOUT IMPLEMENTING ERRNO
#include "../include/socketpp/tcp/basesocket.h"

using namespace std;

/* Basic socket */

tcp::basic_socket::basic_socket()
	: host(NULL),
	  port(0)
{	
	socketfd = socket(AF_INET, SOCK_STREAM, 0); // creates the new socket
	if (socketfd < 0){
		cerr << "basesocket.cc:17:25: Error creating socket descriptor (non-zero return)" << endl;
		return;
	}
	
	_isConnected = false;
}


tcp::basic_socket::basic_socket(const char* _host, int _port)
	: host((char*) _host),
	  port(_port)
{
	socketfd = socket(AF_INET, SOCK_STREAM, 0); // creates the new socket
	if (socketfd < 0){
		cerr << "basesocket.cc:31:44: Error creating socket descriptor (non-zero return)" << endl;
		return;
		/* Consider making a socket exception */
	}
}

tcp::basic_socket::basic_socket(int sockd)
	: socketfd(sockd)
{
}

int
tcp::basic_socket::getSockfd()
{
	return this->socketfd;
}

bool
tcp::basic_socket::isConnected()
{
	int error = 0;
        socklen_t size = sizeof(error);
	
	// SEGMENTATION FAULT
	int ret = getsockopt(socketfd, SOL_SOCKET, SO_ERROR, &error, &size);

	return (ret == 0 && error == 0) ? true : false; // if both are true, then socket is connected
}


int
tcp::basic_socket::connects(const char* _host, int _port)
{

	addr.sin_family      = AF_INET;         // sets the address's family
	addr.sin_port        = htons(_port);     // sets the address's port
	addr.sin_addr.s_addr = inet_addr(_host); // sets the address's host

	if ( connect(socketfd, (struct sockaddr*)&addr, sizeof(addr)) < 0){
		cerr << "basesocket.cc:connects:66: Error connected to server (non-zero return value)" << endl;
		return 1;
	}

	_isConnected = true;
	return 0;
}


int
tcp::basic_socket::connects()
{

	if (host == NULL || port == 0){
		cerr << "basesocket.cc:connects::84: Host and port not set" << endl;
		return -1;

	}
	
	/*
	if (isConnected()){
		cerr << "basesocket.cc:connects::84: Socket already connected" << endl;
		return -2;
	}
	*/

	addr.sin_family      = AF_INET;          // sets the address's family
	addr.sin_port        = htons(port);      // sets the address's port
	addr.sin_addr.s_addr = inet_addr(host);  // sets the address's host

	if ( connect(socketfd, (struct sockaddr*)&addr, sizeof(addr)) < 0){
		cerr << "basesocket.cc:connects:66: Error connected to server (non-zero return value)" << endl;
		return -1;
	}
	
	_isConnected = true;

	return 0;
}

const char*
tcp::basic_socket::getLocalhost()
{
	
	struct sockaddr_in localAddress;
	socklen_t addressLen = sizeof(localAddress);
	getsockname(socketfd, (struct sockaddr*)&localAddress, &addressLen);
	const char* addr = NULL;
 	addr = inet_ntoa(localAddress.sin_addr);
	return addr; // get the local address
}

int
tcp::basic_socket::sends(char* buffer)
{

	int bytes;

	/* First, send the size of buffer */
	int datalen = strlen(buffer); // get sizeof buffer
	int len     = htonl(datalen); // reformat

	bytes = send(socketfd, (char*)&len, sizeof(len), 0); // send the size
	if (bytes < 0){
		cerr << "basesocket.cc:sends: Error sending size of buffer to socket" << endl;
		return -1;
	}

	/* Now acutally send the data */

	bytes = send(socketfd, buffer, datalen, 0);
	if (bytes < 0){
		cerr << "basesocket.cc:sends: Error writing buffer to socket" << endl;
		return -1;
	}

	return 0;

}

int
tcp::basic_socket::sendBuf(char* data, int size)
{
	// make sure connected
	if (!isConnected()){
		cerr << "basesocket.cc:sendBuf:164: Socket not connected" << endl;
		return -2; // not connected
	}
	
	int bytes = send(socketfd, data, size, 0); // get bytes read
	if (bytes < 0){
		cerr << "basesocket.cc:sendBuf:164: No bytes sent" << endl;
		return bytes;
	}
	
	if ((bytes - size) != 0){ /* Not all data sent */
	    return (bytes - size); // return negative not sent
	}

	return bytes; // return number of bytes sent
}

char*
tcp::basic_socket::reads()
{

	char* buffer;
	int bytes, buflen;

	// Read the incoming size 
	bytes = recv(socketfd, (char*)&buflen, sizeof(buflen), 0);
	if (bytes < 0){
		cerr << "basesocket.cc:reads: Error reading size of data" << endl;
		return NULL;
	}
	buflen = ntohl(buflen);

	buffer = new char[buflen+1]; // create a buffer for reading with room for null terminator

	//* Read the data 

	bytes = recv(socketfd, buffer, buflen, 0);
	if (bytes < 0){
		cerr << "basesocket.cc:reads: Error reading data" << endl;
		return NULL;
	}

	buffer[buflen] = '\0'; // set the null terminator

	return buffer;
}

int
tcp::basic_socket::readBuf(char* buffer, int size)
{
	int bytes = recv(socketfd, buffer, size, 0);
	if (bytes < 0){
		cerr << "basesocket.cc:readBuf:225: No bytes read" << endl;
		return -1;
	}

	return bytes;
}

int
tcp::basic_socket::setOpt(int level, int option, const void* val)
{
	socklen_t size = sizeof(val);
	return setsockopt(this->socketfd, level, option,
			  val, size);
}

int
tcp::basic_socket::getOpt(int level, int option, void* val)
{
	socklen_t size = sizeof(val);
	return getsockopt(this->socketfd, level, option,
			  val, &size);
}

int
tcp::basic_socket::setReuseAddr(bool var)
{
	int _val = (int) var;
	return this->setOpt(SOL_SOCKET, SO_REUSEADDR, (void*) &_val);
}

int
tcp::basic_socket::isReuseAddr()
{
	int val = 0;
	int ret = this->getOpt(SOL_SOCKET, SO_REUSEADDR, &val);
	if (ret == -1)
		return ret;
	else
		return val;
}

int
tcp::basic_socket::setKeepAlive(bool var)
{
	int _var = (int) var;
	return this->setOpt(SOL_SOCKET, SO_KEEPALIVE, (void*) &var);
}

int
tcp::basic_socket::isKeepAlive()
{
	int val = 0;
	int ret = this->getOpt(SOL_SOCKET, SO_KEEPALIVE, (void*) &val);
	if (ret == -1)
		return ret;
	else
		return val;
}

void
tcp::basic_socket::closes()
{
	close(socketfd);
}

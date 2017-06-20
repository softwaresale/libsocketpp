

/*
 Header for basic_socket

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


#ifndef SOCKET_PP
#define SOCKET_PP 1

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <streambuf>

using namespace std;

namespace tcp {

class basic_socket
{

protected:
	int                socketfd;
	struct sockaddr_in addr;
	char*              host;
	int                port;
	bool              _isConnected;
	
	
public:
	basic_socket();
	basic_socket(const char* host, int port); // create a new socket class with host and port
	basic_socket(int sockd);            // create a socket class from existing socket descriptor
	
	int   getSockfd();                  // returns the socket descriptor
	char* getLocalhost();               // gets the localhost of the socket

	int connects(const char*, int);
	int connects();                      // connects to the server if address already set

	bool isConnected();                 // true if the socket is connected

       	int sends(char*);
	int sendBuf(char*, int);

	char* reads();
	int   readBuf(char*, int);


	
	void closes();                      // closes the connection

};

}

#endif

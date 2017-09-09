
/*
    server.cc header

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
namespace socketpp::tcp
{

class Server
{

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

	int setReuseAddr(bool var = true);
	int isReuseAddr();

	int setKeepAlive(bool var = true);
	int isKeepAlive();

	tcp::Socket& accepts();           // accepts a socket connection and returns a socket
	int          acceptfd();          // returns the connected socket descriptor

	void closes();                   // closes the server

};

}
#endif

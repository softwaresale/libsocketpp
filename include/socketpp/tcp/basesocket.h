

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

namespace socketpp::tcp
{

class basic_socket
{

private:


protected:
	int                socketfd;
	struct sockaddr_in addr;
	char*              host;
	int                port;
        char*              salt; // current salt value
        char*              cliSalt; // salt of client
        int                isSecure; // whether or not in secure mode
        int                hashExchanged; // if exchangeHashes() has been executed
        
public:
        /*
	 * Constructors:
	 * -------------
	 * basic_socket()                      --> constructs a basic socket object
	 * basic_socket(const char*, int)      --> creates a socket object with 
         *                                         connection data
         * basic_socket(const char*, int, int) --> same as before, but if last
         *                                         value is true, connects
	 * basic_socket(int)                   --> creates a socket object around a 
                                                   socket descriptor
	 */
	basic_socket();
	basic_socket(const char*, int);
        basic_socket(const char*, int, int);
	basic_socket(int);
    
	/*
	 * getSockFd
	 * ---------
	 * Returns the internal socket descriptor as an integer
	 */
	int   getSockfd();

	/*
	 * getLocalHost
	 * ------------
	 * Returns a string containing the local IP address of the machine
	 */
	const char* getLocalhost(); 
        
        /*
         * getLocalPort()
         * --------------
         * Returns the port currently being used
         */
        int getLocalPort();

	/*
	 * connects(const char*, int) --> connects to server with given data
	 *                                returns non-zero on success
	 * connects()                 --> connects to server with already
	 *                                given connection data in constructor
	 */
	int connects(const char*, int);
	int connects();                      
        
	/*
	 * isConnected()
	 * -------------
	 * true if socket is connected to server
	 */
	bool isConnected();                 
        
	/*
	 * sends(char*)
	 * ------------
	 * Sends a string to a server, returns -1 on failure
	 */
       	int sends(char*);

	/*
	 * sendBuf(char*, int)
	 * -------------------
	 * sends a buffer for `int` number of bytes
	 */
	int sendBuf(char*, int);

	/*
	 * reads()
	 * -------
	 * reads and returns a buffer from the other connections
	 */
	char* reads();
	int   readBuf(char*, int);
        
	int setOpt(int, int, const void*);
	int getOpt(int, int, void*);

	/*
	 * Sets if an address should be reused (option SO_REUSEADDR)
	 * setReuseAddr --> if param is false, turns option off
	 * isReuseAddr  --> 1 if true, 0 if false
	 */
	int setReuseAddr(bool var = true);
	int isReuseAddr();

	/*
	 * Set if socket should stay alive
	 */
	int setKeepAlive(bool var = true);
	int isKeepAlive();

	/*
	 * getPeerName(char*)
	 * ------------------
	 * Places the peer address into the provided buffer and
	 * returns the struct sockaddr
	 *
	 */
	char* getPeerName();
	
	void closes();                      // closes the connection

};
        
}

#endif

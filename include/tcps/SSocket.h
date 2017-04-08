#ifndef SSOCKET_H
#define SSOCKET_H 1

/* This is a socket built with openssl
 * We use the basic socket functionality
 * for creating a socketfd and binding it
 * to an address, but from there, we are going
 * to change it around
 *
 * Note: in this file, I am trying out a new
 * coding style; that is, the official GNU
 * coding style. So, if it looks different,
 * just know that */

#include <tcp/Socket.h> // for getting the socketfd
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

using namespace std;
using namespace tcp;

// start

/* This function is called in all constructors.
 * It sets up the basic file functionality */
void
initssl();

/* Called on all closes. Destroys an ssl instance */
void
destssl();

/* Shuts down an ssl session 
 * @param int -- ssl session to shut down */
void
shutdownssl(SSL*);

namespace tcps
{

/* Note: the method name's are based off of that of the tcp::Socket */

class SSocket {

private:

protected:
	SSL*     sock_ssl; // pointer to ssl data
	SSL_CTX* ssl_ctx;  // pointer to ssl context data (?)
	char*    host;     // general address /
	int      port;     // connection data

public:
	SSocket(char* host, int port); // basic socket constructor with connection data
	SSocket();                     // basic socket constructor
	
	int   connects();
	int   connects(char*, int);

	int   sends(char*);

	char* reads();

	void  closes();
};

}

#endif

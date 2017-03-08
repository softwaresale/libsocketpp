#ifndef FTPSERVER_H
#define FTPSERVER_H 1

#include <tar.h>
#include "ftp.h"
#include "../tcp/socket.h"
#include "../tcp/server.h"

using namespace std;
using namespace tcp;

/* This class is a server for the Ftp class
 * @author Charlie Sale
 *
 */

// this is part of ftp namespace
namespace ftp {

class FtpServer : public Server {

private:

protected:

public:
	/* Call parent constructors */
	FtpServer(int port) : Server(port) {  }
	FtpServer()         : Server()     {  }
	
	// specific methods
	
	/* Accepts a Ftp class pointer
	 * @return -- connected FTP class */
	Ftp* acceptFtp();

};

}

#endif

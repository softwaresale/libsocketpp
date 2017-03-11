#include <iostream>
#include <cstring>
#include "../header/tcp/server.h"
#include "../header/tcp/socket.h"
#include "../header/ftp/ftp.h"
#include "../header/ftp/ftpserver.h"

using namespace std;
using namespace tcp;

ftp::Ftp* ftp::FtpServer::acceptFtp(){

	if (!this->isBound())
		return NULL; // server is not bound

	ftp::Ftp* tmp = new Ftp(this->acceptfd()); // accept a connection
						 // and return a new Ftp Class
						 

	return tmp; // return tmp
}


/* This is a basic class for inheriting streambuf to make a socket class */

#ifndef BASIC_SOCKBUF_H
#define BASIC_SOCKBUF_H 1

#include <streambuf>
#include <socketpp/tcp/basesocket.h>

using namespace std;

namespace tcp
{

class Basic_Sockbuf
	: public streambuf, 
	  public tcp::Basic_socket
{

 private:
  
 protected:

	virtual streambuf::int_type underflow();
	virtual streambuf::int_type overflow(char ch);
	
 public:
	//Basic_Sockbuf();                      // creates a new streambuf with basic socket
	Basic_Sockbuf(char* host, int port);
	Basic_Sockbuf(int sockfd);
};
 
};

#endif // BASIC_SOCKBUF_H

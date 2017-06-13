
#include <socketpp/tcp/socket.h>
#include <socketpp/tcp/basesocket.h>
#include <socketpp/tcp/basesockbuf.h>
#include <ostream>
#include <iostream>

using namespace std;

tcp::Socket::Socket(char* host, int port)
	: tcp::Basic_Sockbuf(host, port),
       	  tcp::Basic_Sockstream(this)
{
	// constructor called
}

tcp::Socket::Socket(int sockfd)
	: tcp::Basic_Sockbuf(sockfd),
	  tcp::Basic_Sockstream(this)
{

}

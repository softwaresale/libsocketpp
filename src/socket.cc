
#include <socketpp/tcp/basesocket.h>
#include <socketpp/tcp/socket.h>
#include <iostream>
#include <socketpp/tcp/basesockbuf.h>

using namespace std;

tcp::Socket::Socket(const char* host, int port)
	: basic_socket((char*) host, port),
	  iostream(new base_sock_buf(this))
{

}

tcp::Socket::Socket(int sockfd)
	: basic_socket(sockfd),
	  iostream(new base_sock_buf(this))
{

}

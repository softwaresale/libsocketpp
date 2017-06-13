
#include <tcp/socket.h>
#include <tcp/basesocket.h>
#include <tcp/basesockbuf.h>
#include <ostream>

using namespace std;

tcp::Socket::Socket()
	: tcp::Basic_Sockstream(NULL)
{

}

tcp::Socket::Socket(char* host, int port)
	: tcp::Basic_Sockstream(new tcp::Basic_Sockbuf(host, port))
{

}

tcp::Socket::Socket(int sockfd)
	: tcp::Basic_Sockstream(new tcp::Basic_Sockbuf(sockfd))
{

}

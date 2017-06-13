
#include <tcp/socket.h>
#include <tcp/basesocket.h>
#include <tcp/basesockbuf.h>
#include <ostream>

using namespace std;

tcp::Socket::Socket()
	: ostream()
{
	
}

tcp::Socket::Socket(char* host, int port)
	: ostream(new tcp::Basic_Sockbuf(host, port))
{

}

tcp::Socket::Socket(int sockfd)
	: ostream(new tcp::Basic_Sockbuf(sockfd))
{

}

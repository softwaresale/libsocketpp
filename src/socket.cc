
#include <socketpp/tcp/basesocket.h>
#include <socketpp/tcp/basereadbuf.h>
#include <socketpp/tcp/basewritebuf.h>
#include <socketpp/tcp/basesockout.h>
#include <socketpp/tcp/basesockin.h>
#include <ostream>
#include <istream>
#include <socketpp/tcp/socket.h>

using namespace std;

tcp::Socket::Socket(const char* host, int port)
	: tcp::basic_socket(host, port),
	  istream(new tcp::basic_read_buf(this)),
	  ostream(new tcp::basic_write_buf(this))
{
	
}

tcp::Socket::Socket(int sockfd)
  : tcp::basic_socket(sockfd),
    istream(new tcp::basic_read_buf(this)),
    ostream(new tcp::basic_write_buf(this))
{

}


#include <tcp/basesockbuf.h>
#include <streambuf>
#include <cstdlib>

using namespace std;

tcp::Basic_Sockbuf::Basic_Sockbuf()
	: tcp::Basic_socket()
{
	
}

tcp::Basic_Sockbuf::Basic_Sockbuf(char* host, int port)
	: tcp::Basic_socket(host, port)
{
	
}

tcp::Basic_Sockbuf::Basic_Sockbuf(int sockfd)
	: tcp::Basic_socket(sockfd)
{

}

streambuf::int_type
tcp::Basic_Sockbuf::overflow(char ch)
{
	if (!this->isConnected()){
		return EOF; // socket is not connected
	}
	
	if (ch != EOF){
		int ret = this->sends(&ch);
		if (ret != 0)
			return EOF;
	}

	return ch;
}

streambuf::int_type
tcp::Basic_Sockbuf::underflow()
{
	char ch = this->readc(); // read a character from the socket
	if (ch == EOF)
		return EOF;
	
	return ch; // return character
}

// Give this a shot



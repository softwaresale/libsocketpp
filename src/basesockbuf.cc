
#include <socketpp/tcp/basesockbuf.h>
#include <streambuf>
#include <cstdlib>
#include <iostream>

using namespace std;

/*
tcp::Basic_Sockbuf::Basic_Sockbuf()
	: tcp::Basic_socket()
{
	
}
*/

tcp::Basic_Sockbuf::Basic_Sockbuf(char* host, int port)
	: tcp::Basic_socket(host, port)
{
	int ret = this->connects(); // connect to the host
	if (ret != 0){
       		cerr << "Basic_Sockbuf ctor: Error connecting" << endl;
	       	// throw exception()
	}
}

tcp::Basic_Sockbuf::Basic_Sockbuf(int sockfd)
	: tcp::Basic_socket(sockfd)
{
	if (!this->isConnected()){
		int ret = this->connects();
		if (ret != 0){
			cerr << "Basic_Sockbuf ctor: Error connecting" << endl;
			// throw exception()
		}
		
	}
}

streambuf::int_type
tcp::Basic_Sockbuf::overflow(char ch)
{
	/*
	if (!this->isConnected()){
		return EOF; // socket is not connected
	}
	*/
	
	if (ch != EOF){
		int ret = this->sendc(ch);
		if (ret != 0)
			return EOF;
	}

	return ch;
}

streambuf::int_type
tcp::Basic_Sockbuf::underflow()
{
	if (gptr() < egptr()) // buffer not exhausted
		return traits_type::to_int_types(*gptr());

	char* base = &buffer_.front();
	char* start = base;

	if (eback() == base){
		// arrangement for putback chars
		memmove(base, egptr() - put_back_, put_back_);
		start += put_back_;
	}

	// start is now the start of the buffer
	// read socket to the provided buffer

	int ret = this->readc(
	
	return ch; // return character
}

// Give this a shot



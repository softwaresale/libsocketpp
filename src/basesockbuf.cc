
#include <socketpp/tcp/basesockbuf.h>
#include <streambuf>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <vector>

using namespace std;

/*
tcp::Basic_Sockbuf::Basic_Sockbuf()
	: tcp::Basic_socket()
{
	
}
*/

tcp::Basic_Sockbuf::Basic_Sockbuf(Basic_socket* _sock)
	: sock(_sock);
{
	int ret = sock->connects(); // connect to the host
	if (ret != 0){
       		cerr << "Basic_Sockbuf ctor: Error connecting" << endl;
	       	// throw exception()
	}

	// set some internal data
	put_back = max(8, size_t(1));
	buffer = vector<char>(max(256, put_back) + put_back);
}

streambuf::int_type
tcp::Basic_Sockbuf::overflow(char ch)
{

	
	
}

streambuf::int_type
tcp::Basic_Sockbuf::underflow()
{
	if (gptr() < egptr()) // buffer not exhausted
		return traits_type::to_int_type(*gptr());

	char* base = &buffer_.front();
	char* start = base;

	if (eback() == base){
		// arrangement for putback chars
		memmove(base, egptr() - put_back_, put_back_);
		start += put_back_;
	}

	// start is now the start of the buffer
	// read socket to the provided buffer

	int ret = sock->reads(start, buffer.size() - (start - base));
	if (ret == 0)
		return traits_type::eof();

	setg(base, start, start + n);
	
	return traits_type::to_int_type(*gptr());
}

// Give this a shot



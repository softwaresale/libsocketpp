
#include <socketpp/tcp/basereadbuf.h>
#include <socketpp/tcp/basesocket.h>
#include <streambuf>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

tcp::basic_read_buf::basic_read_buf(basic_socket* _sock)
	: sock(_sock),
	  putback(std::max(8, (int) size_t(1))),
	  buffer(std::max(256, (int) putback) + putback)
{
	// set up the buffer
	char* end = &buffer.front() + buffer.size();
	setg(end, end, end);
}

streambuf::int_type
tcp::basic_read_buf::underflow()
{
	if (gptr() < egptr()) // buffer not exhausted
		return traits_type::to_int_type(*gptr());

	char* base = &buffer.front();
	char* start = base;
	
	if (eback() == base){
		memmove(base, egptr() - putback, putback); // this little mf is causing a segmentation fault
		start += putback;
	}

	// read into the buffer from socket
	int ret = sock->readBuf(start, buffer.size() - (start - base));
	if (ret < 0){
		cerr << "tcp::basic_read_buf:underflow(): sock->readBuf returned lower than 0 value" << endl;
		return traits_type::eof();
	}

	// set pointers
	setg(base, start, start + ret);

	return traits_type::to_int_type(*gptr());
}



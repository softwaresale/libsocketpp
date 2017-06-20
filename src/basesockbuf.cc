
#include <socketpp/tcp/basesockbuf.h>
#include <socketpp/tcp/basesocket.h>
#include <streambuf>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <cassert>
#include <iostream>

using namespace std;

tcp::base_sock_buf::base_sock_buf(basic_socket* _sock)
	: sock(_sock),
	  //putback(std::max(8, (int) size_t(1))),
	  //buffer(std::max(256, (int) putback) + putback)
	  buffer(256)
{
	// set up the read pointers
	char* end = &buffer.front() + buffer.size();
	setg(end, end, end);

	// set up the write pointers
	char* base = &buffer.front();
	setp(base, base + buffer.size()); // -1 to make overflow easier

}

streambuf::int_type
tcp::base_sock_buf::underflow()
{
	if (gptr() < egptr()){ // buffer not exhausted
		cout << "basereadbuf.cc:underflow: Buffer not exhausted" << endl;
		return traits_type::to_int_type(*gptr());
	}
	
	int putback = gptr() - eback();
	if (putback > 4)
		putback = 4;
	
	char* base = &buffer.front();
	char* start = base;
	
	if (eback() == base){
		memmove(base, egptr() - putback, putback);
		start += putback;
	}

	// read into the buffer from socket

	int ret = sock->readBuf(start, buffer.size() - (start - base));
	
	cout << "RETCODE: " << ret << endl;
	
	cout << "Buffer: " << start << endl;
	
	if (ret <= 0){
		cerr << "tcp::base_sock_buf:underflow(): sock->readBuf returned lower than 0 value" << endl;
		return traits_type::eof();
	}
	
	// set pointers
	setg(base, start, start + ret);

	return traits_type::to_int_type(*gptr());
}


streambuf::int_type
tcp::base_sock_buf::overflow(char ch)
{
	if (ch != traits_type::eof()){
		
		assert(less_equal<char*>()(pptr(), epptr()));
		*pptr() = ch;
		pbump(1);

		// write data
		ptrdiff_t size = pptr() - pbase();
		pbump(-size);
		
		int ret = sock->sendBuf(pbase(), size); // should send data
		if (ret <= 0){
			cout << "RET: " << ret << endl;
			cerr << "basesockbuf.cc:overflow: sock send not bytes" << endl;
			return traits_type::eof();
		} 
		cout << "RET: " << ret << endl;

		return ch;
		
	}
	cerr << "basesockbuf.cc:overflow: Char is EOF" << endl;
	
	return traits_type::eof();
}

int
tcp::base_sock_buf::sync()
{
	ptrdiff_t size = pptr() - pbase();
	pbump(-size);
	int ret = sock->sendBuf(pbase(), size);
	if (ret <= 0){
		cerr << "basesockbuf.cc:sync: sock sent no bytes" << endl;
		return traits_type::eof();
	}
	
	return ret;
}

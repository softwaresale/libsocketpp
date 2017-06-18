
#include <socketpp/tcp/basewritebuf.h>
#include <socketpp/tcp/basesocket.h>
#include <streambuf>
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

tcp::basic_write_buf::basic_write_buf(basic_socket* _sock)
	: sock(_sock),
	  buffer(257)
{
	char* base = &buffer.front();
	setp(base, base + buffer.size() - 1); // -1 to make overflow easier
}

streambuf::int_type
tcp::basic_write_buf::overflow(char ch)
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
			cerr << "basewritebuf.cc:overflow: sock send not bytes" << endl;
			return traits_type::eof();
		}

		return ch;
		
	}

	return traits_type::eof();
}

int
tcp::basic_write_buf::sync()
{
	ptrdiff_t size = pptr() - pbase();
	pbump(-size);
	int ret = sock->sendBuf(pbase(), size);
	if (ret <= 0){
		cerr << "basewritebuf.cc:sync: sock sent no bytes" << endl;
		return traits_type::eof();
	}
	return ret;
}

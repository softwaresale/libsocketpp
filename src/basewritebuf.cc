
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
	cout << "Calling overflow..." << endl;

	if (ch != traits_type::eof()){
		
		cout << "Asserting value..." << endl;
		assert(less_equal<char*>()(pptr(), epptr()));
		cout << "Setting value and bumping" << endl;
		*pptr() = ch;
		pbump(1);

		// write data
		cout << "Getting size of pointers..." << endl;
		ptrdiff_t size = pptr() - pbase();
		pbump(-size);
		
		cout << "Sending buffer..." << endl;
		int ret = sock->sendBuf(pbase(), size); // should send data
		if (ret <= 0){
			cout << "RET: " << ret << endl;
			cerr << "basewritebuf.cc:overflow: sock send not bytes" << endl;
			return traits_type::eof();
		} 
		cout << "RET: " << ret << endl;

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

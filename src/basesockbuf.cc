
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
	  putback(std::max(8, (int) size_t(1))),
	  buffer(std::max(256, (int) putback) + putback)
{
	// set up the read pointers
	char* end = &buffer.front() + buffer.size();
	setg(end, end, end);

	// set up the write pointers
	char* base = &buffer.front();
	setp(base, base + buffer.size() - 1); // -1 to make overflow easier

}

streambuf::int_type
tcp::base_sock_buf::underflow()
{
	cout << "basereadbuf.cc:underflow: Calling underflow..." << endl;
	if (gptr() < egptr()){ // buffer not exhausted
		cout << "basereadbuf.cc:underflow: Buffer not exhausted" << endl;
		return traits_type::to_int_type(*gptr());
	}

	char* base = &buffer.front();
	char* start = base;
	
	if (eback() == base){
		memmove(base, egptr() - putback, putback); // this little mf is causing a segmentation fault
		start += putback;
	}

	// read into the buffer from socket
	cout << "Reading data into buffer" << endl;

	// try using a system call for this one
	//int ret = read(sock->getSockfd(), start, buffer.size() - (start - base));
	int ret = sock->readBuf(start, buffer.size() - (start - base));
	 //cout << "Socket ID: " << sock->getSockfd() << endl;
	 //char* charbuffer = new char[32];
	 //ssize_t ret = read(sock->getSockfd(), charbuffer, 32-1);
	
	cout << "RETCODE: " << ret << endl;
	
	if (ret <= 0){
		cerr << "tcp::base_sock_buf:underflow(): sock->readBuf returned lower than 0 value" << endl;
		return traits_type::eof();
	}
	
	cout << "Buffer contents: " << buffer.data() << endl;
	
	// set pointers
	cout << "Setting pointers" << endl;
	setg(base, start, start + ret);
	
	cout << *gptr() << endl;

	return traits_type::to_int_type(*gptr());
}


streambuf::int_type
tcp::base_sock_buf::overflow(char ch)
{
	cout << "basesockbuf.cc:overflwo: Calling overflow..." << endl;

	if (ch != traits_type::eof()){
		
		cout << "Asserting value..." << endl;
		assert(less_equal<char*>()(pptr(), epptr()));
		cout << "Setting value and bumping" << endl;
		*pptr() = ch;
		cout << "pptr() = " << ch << endl;
		pbump(1);

		// write data
		cout << "Getting size of pointers..." << endl;
		ptrdiff_t size = pptr() - pbase();
		cout << "Size: " << size << endl;
		pbump(-size);
		
		cout << "Sending buffer..." << endl;
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
	cout << "basesockbuf.cc:sync: Calling sync..." << endl;
	ptrdiff_t size = pptr() - pbase();
	cout << "basesockbuf.cc:sync: Size: " << size << endl;
	pbump(-size);
	int ret = sock->sendBuf(pbase(), size);
	cout << "basesockbuf.cc:sync: RET: " << ret << endl;
	if (ret <= 0){
		cerr << "basesockbuf.cc:sync: sock sent no bytes" << endl;
		return traits_type::eof();
	}
	
	return ret;
}

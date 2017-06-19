
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
	cout << "basereadbuf.cc:underflow: Calling underflow..." << endl;
	if (gptr() < egptr()){ // buffer not exhausted
		cout << "basereadbuf.cc:underflow: Buffer not exhausted" << endl;
		return traits_type::to_int_type(*gptr());
	}

	char* base = &buffer.front();
	char* start = base;
	cout << "Start: " << start << endl;
	
	cout << "Setting eback()..." << endl;
	if (eback() == base){
		memmove(base, egptr() - putback, putback); // this little mf is causing a segmentation fault
		start += putback;
	}

	// read into the buffer from socket
	cout << "Reading data into buffer" << endl;

	char* _buffer = new char[32]; // make a large buffer (note: dynamically allocate this later)
	// int ret = sock->readBuf(start, buffer.size() - (start - base));
	int ret = sock->readBuf(_buffer, sizeof(buffer)); // read the buffer into the thing

	if (ret < 0){
		cerr << "tcp::basic_read_buf:underflow(): sock->readBuf returned lower than 0 value" << endl;
		return traits_type::eof();
	}
	
	int len = strlen(_buffer);
	_buffer[len] = '\0'; // null terminate	
	
	for (int i = 0; i < strlen(_buffer); i++){
		buffer.push_back(_buffer[i]); // push each character into the main buffer
	}

	cout << "Buffer contents: " << buffer.data() << endl;
	
	// set pointers
	cout << "Setting pointers" << endl;
	setg(base, start, start + ret);

	return traits_type::to_int_type(*gptr());
}



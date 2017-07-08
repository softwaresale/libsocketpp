
/*
  This class is a derivation from std::streambuf that allows a stream
  to interface with a socket. It implements an internal `basic_socket*`
  that sends and recieves data.

    Copyright (C) 2017  Charlie Sale

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


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
	  buffer(256),
	  outBuf(256)
{
	// set up the read pointers
	char* end = &buffer.front() + buffer.size();
	setg(end, end, end);

	// set up the write pointers
	char* base = &outBuf.front();
	setp(base, base + outBuf.size() - 1); // -1 to make overflow easier

}

streambuf::int_type
tcp::base_sock_buf::underflow()
{
	if (gptr() < egptr()){ // buffer not exhausted
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
	
	if (ret < 0){
		cerr << "tcp::base_sock_buf:underflow(): sock->readBuf returned lower than 0. RET: " << ret << endl;
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
			cerr << "basesockbuf.cc:overflow: sock send not bytes. Ret: " << ret << endl;
			return traits_type::eof();
		}
		 

		return ch;
	}
		
	
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

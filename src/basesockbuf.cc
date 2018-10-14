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

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <base/basesockbuf.h>
#include <base/basesocket.h>
#include <streambuf>
#include <unistd.h>
#include <vector>
#include <sys/un.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

template <typename _AddrType>
lsock::base::BaseSocketBuf<_AddrType>::BaseSocketBuf(lsock::base::BaseSocket<lsock::base::Connect, _AddrType> *_sock)
    : m_sock(_sock),
      // putback(std::max(8, (int) size_t(1))),
      // m_in_buffer(std::max(256, (int) putback) + putback)
      m_in_buffer(2048), m_out_buffer(256)
{
    // set up the read pointers
    char *end = &m_in_buffer.front() + m_in_buffer.size();
    setg(end, end, end);

    // set up the write pointers
    char *base = &m_out_buffer.front();
    setp(base, base + m_out_buffer.size() - 1); // -1 to make overflow easier
}

template <typename _AddrType>
std::streambuf::int_type
lsock::base::BaseSocketBuf<_AddrType>::underflow()
{
    if (gptr() < egptr()) { // buffer not exhausted
	return traits_type::to_int_type(*gptr());
    }

    char *base = &m_in_buffer.front();
    char *start = base;

    // read into the buffer from socket

    int ret;

    ret = m_sock->simple_read(start, m_in_buffer.size() - (start - base));

    if (ret < 0) {
	return traits_type::eof();
    }

    // set pointers
    setg(base, start, start + ret);

    return traits_type::to_int_type(*gptr());
}
template <typename _AddrType>
std::streambuf::int_type
lsock::base::BaseSocketBuf<_AddrType>::overflow(char ch)
{
    if (ch != traits_type::eof()) {

	assert(std::less_equal<char *>()(pptr(), epptr()));
	*pptr() = ch;
	pbump(1);

	// write data
	ptrdiff_t size = pptr() - pbase();
	pbump(-size);

	int ret = m_sock->simple_write(pbase(), size); // should send data
	if (ret <= 0) {
	    return traits_type::eof();
	}

	return ch;
    }

    return traits_type::eof();
}

template <typename _AddrType>
int
lsock::base::BaseSocketBuf<_AddrType>::sync()
{
    ptrdiff_t size = pptr() - pbase();
    pbump(-size);
    int ret = m_sock->simple_write(pbase(), size);
    if (ret <= 0)
    {
        return traits_type::eof();
    }

    return ret;
}

template class lsock::base::BaseSocketBuf<struct sockaddr_in>;
template class lsock::base::BaseSocketBuf<struct sockaddr_un>;

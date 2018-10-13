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

lsock::BaseSocketBuf::BaseSocketBuf(BaseSocket *_sock)
    : m_sock(_sock),
      m_in_buffer(2048),
      m_out_buffer(256)
{
    // set up the read pointers
    char *end = &m_in_buffer.front() + m_in_buffer.size();
    setg(end, end, end);

    // set up the write pointers
    char *base = &m_out_buffer.front();
    setp(base, base + m_out_buffer.size() - 1); // -1 to make overflow easier
}

std::streambuf::int_type
lsock::BaseSocketBuf::underflow()
{
    if (!m_sock->connected())
        return traits_type::eof();

    if (gptr() < egptr()) { // m_in_buffer not exhausted
        return traits_type::to_int_type(*gptr());
    }

    char *base = &m_in_buffer.front();
    char *start = base;

#if 0
    if (eback() == base) {
        memmove(base, egptr() - putback, putback);
        start += putback;
    }
#endif

    // read into the m_in_buffer from socket

    int ret;
    ret = m_sock->simple_read(start, m_in_buffer.size() - (start - base));
    if (ret < 0) {
        return traits_type::eof();
    }

    // set pointers
    setg(base, start, start + ret);

    return traits_type::to_int_type(*gptr());
}

std::streambuf::int_type
lsock::BaseSocketBuf::overflow(char ch)
{
    if (!m_sock->connected())
        return traits_type::eof();

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

int
lsock::BaseSocketBuf::sync()
{
    if (!m_sock->connected())
        return traits_type::eof();

    ptrdiff_t size = pptr() - pbase();
    pbump(-size);
    int ret = m_sock->simple_write(pbase(), size);
    if (ret <= 0) {
        return traits_type::eof();
    }

    return ret;
}

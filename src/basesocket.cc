
/*
  basesocket.cc -- Implement BaseSocket class
  Copyright (C) 2018  Charlie Sale

  This file is part of libsocketpp

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

#include <functional>
#include <memory>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <base/basesocket.h>
#include <base/addr.h>

template <typename _ConnectFunc, typename _AddrType>
lsock::base::Socket<_ConnectFunc, _AddrType>::Socket(int family, int type, int proto)
{
    m_sockfd = socket(family, type, proto);
}

template <typename _ConnectFunc, typename _AddrType>
lsock::base::Socket<_ConnectFunc, _AddrType>::Socket(int sfd)
    : m_sockfd(sfd)
{
}

template <typename _ConnectFunc, typename _AddrType>
lsock::base::Socket<_ConnectFunc, _AddrType>::~Socket()
{
    disconnect();
}

template <typename _ConnectFunc, typename _AddrType>
int
lsock::base::Socket<_ConnectFunc, _AddrType>::connect(lsock::base::SockAddr<_AddrType> *ptr)
{
    return m_connector(m_sockfd, ptr->get(), ptr->size());
}

template <typename _ConnectFunc, typename _AddrType>
ssize_t
lsock::base::Socket<_ConnectFunc, _AddrType>::simple_write(char *buf, size_t len, int flags)
{
    return send(m_sockfd, buf, len, flags);
}

template <typename _ConnectFunc, typename _AddrType>
ssize_t
lsock::base::Socket<_ConnectFunc, _AddrType>::simple_read(char *buf, size_t len, int flags)
{
    return recv(m_sockfd, buf, len, flags);
}

template <typename _ConnectFunc, typename _AddrType>
void
lsock::base::Socket<_ConnectFunc, _AddrType>::disconnect(void)
{
    close(m_sockfd);
}

/*
  Define used template classes
*/
template class lsock::base::Socket<lsock::base::Connect, struct sockaddr_in>;
template class lsock::base::Socket<lsock::base::Bind,    struct sockaddr_in>;
template class lsock::base::Socket<lsock::base::Connect, struct sockaddr_un>;
template class lsock::base::Socket<lsock::base::Bind,    struct sockaddr_un>;

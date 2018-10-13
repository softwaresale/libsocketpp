
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

//#include <config.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <base/basesocket.h>

lsock::BaseSocket::BaseSocket(int domain, int type, int proto)
    : m_isconnected(false)
{
    // Just create a new socket
    m_sockfd = socket(domain, type, proto);
    if (m_sockfd < 0) {
        // TODO: Handle error
    }
}

lsock::BaseSocket::BaseSocket(int sfd)
    : m_sockfd(sfd),
      m_isconnected(false)
{
}

lsock::BaseSocket::~BaseSocket()
{
    this->disconnect();
}

void
lsock::BaseSocket::setSfd(int sfd)
{
    m_sockfd = sfd;
}

int
lsock::BaseSocket::getSfd()
{
    return m_sockfd;
}

ssize_t
lsock::BaseSocket::simple_read(char *buf, size_t len, int flags)
{
    return recv(m_sockfd, buf, len, flags);
}

ssize_t
lsock::BaseSocket::simple_write(char *data, size_t len, int flags)
{
    return send(m_sockfd, data, len, flags);
}

void
lsock::BaseSocket::disconnect()
{
    close(m_sockfd);
}

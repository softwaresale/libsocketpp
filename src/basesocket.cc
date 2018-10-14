
#include <functional>
#include <memory>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <base/basesocket.h>
#include <base/addr.h>

template <typename _ConnectFunc, typename _AddrType>
lsock::base::BaseSocket<_ConnectFunc, _AddrType>::BaseSocket(int family, int type, int proto)
{
    m_sockfd = socket(family, type, proto);
}

template <typename _ConnectFunc, typename _AddrType>
lsock::base::BaseSocket<_ConnectFunc, _AddrType>::BaseSocket(int sfd)
    : m_sockfd(sfd)
{
}

template <typename _ConnectFunc, typename _AddrType>
lsock::base::BaseSocket<_ConnectFunc, _AddrType>::~BaseSocket()
{
    disconnect();
}

template <typename _ConnectFunc, typename _AddrType>
int
lsock::base::BaseSocket<_ConnectFunc, _AddrType>::connect(lsock::base::BaseSockAddr<_AddrType> *ptr)
{
    return m_connector(m_sockfd, ptr->get(), ptr->size());
}

template <typename _ConnectFunc, typename _AddrType>
ssize_t
lsock::base::BaseSocket<_ConnectFunc, _AddrType>::simple_write(char *buf, size_t len, int flags)
{
    return send(m_sockfd, buf, len, flags);
}

template <typename _ConnectFunc, typename _AddrType>
ssize_t
lsock::base::BaseSocket<_ConnectFunc, _AddrType>::simple_read(char *buf, size_t len, int flags)
{
    return recv(m_sockfd, buf, len, flags);
}

template <typename _ConnectFunc, typename _AddrType>
void
lsock::base::BaseSocket<_ConnectFunc, _AddrType>::disconnect(void)
{
    close(m_sockfd);
}

/*
  Define used template classes
*/
template class lsock::base::BaseSocket<lsock::base::Connect, struct sockaddr_in>;
template class lsock::base::BaseSocket<lsock::base::Bind,    struct sockaddr_in>;
template class lsock::base::BaseSocket<lsock::base::Connect, struct sockaddr_un>;
template class lsock::base::BaseSocket<lsock::base::Bind,    struct sockaddr_un>;


#include <base/addr.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

#include <base/addr.h>

template <typename _Address>
lsock::base::SockAddr<_Address>::SockAddr()
{
    memset(&m_addr, 0, sizeof(_Address));
}

template <typename _Address>
struct sockaddr *
lsock::base::SockAddr<_Address>::get()
{
    return (struct sockaddr *) &m_addr;
}

template <typename _Address>
socklen_t
lsock::base::SockAddr<_Address>::size()
{
    return sizeof(_Address);
}

template class lsock::base::SockAddr<struct sockaddr_un>;
template class lsock::base::SockAddr<struct sockaddr_in>;

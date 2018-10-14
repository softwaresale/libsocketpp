#include <memory>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <base/addr.h>
#include <base/basesocket.h>
#include <base/baseserver.h>
#include <base/basesockstream.h>
#include <tcp/socket.h>

template <typename _AddrType>
lsock::base::Server<_AddrType>::Server(int family, int type, int proto)
    : lsock::base::Socket<Bind, _AddrType>(family, type, proto)
{ }

template <typename _AddrType>
lsock::base::Server<_AddrType>::Server(int sfd)
    : lsock::base::Socket<Bind, _AddrType>(sfd)
{ }

template <typename _AddrType>
lsock::base::Server<_AddrType>::~Server()
{
    lsock::base::Socket<Bind, _AddrType>::disconnect();
}

template <typename _AddrType>
int
lsock::base::Server<_AddrType>::connect(lsock::base::SockAddr<_AddrType> *addr)
{
    int ret = lsock::base::Socket<lsock::base::Bind, _AddrType>::connect(addr);
    if (ret < 0)
        return -1;

    return listen(this->getSfd(), 5); // TODO: fix arbitrary
}

template <typename _AddrType>
std::unique_ptr<lsock::base::SocketStream<_AddrType>>
lsock::base::Server<_AddrType>::accept_basic()
{
    int sfd = accept(this->getSfd(), nullptr, nullptr);
    if (sfd < 0)
      return nullptr;

    std::unique_ptr<
      lsock::base::SocketStream<_AddrType>
      > ptr(new lsock::base::SocketStream<_AddrType>(sfd));

    return ptr;
}

template class lsock::base::Server<struct sockaddr_in>;
template class lsock::base::Server<struct sockaddr_un>;

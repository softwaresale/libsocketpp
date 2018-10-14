#include <memory>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <base/addr.h>
#include <base/basesocket.h>
#include <base/baseserver.h>
#include <base/basesockstream.h>
#include <inet/tcpsocket.h>

template <typename _AddrType>
lsock::base::BaseServer<_AddrType>::BaseServer(int family, int type, int proto)
    : lsock::base::BaseSocket<Bind, _AddrType>(family, type, proto)
{ }

template <typename _AddrType>
lsock::base::BaseServer<_AddrType>::BaseServer(int sfd)
    : lsock::base::BaseSocket<Bind, _AddrType>(sfd)
{ }

template <typename _AddrType>
lsock::base::BaseServer<_AddrType>::~BaseServer()
{
    lsock::base::BaseSocket<Bind, _AddrType>::disconnect();
}

template <typename _AddrType>
int
lsock::base::BaseServer<_AddrType>::connect(lsock::base::BaseSockAddr<_AddrType> *addr)
{
    int ret = lsock::base::BaseSocket<lsock::base::Bind, _AddrType>::connect(addr);
    if (ret < 0)
        return -1;

    return listen(this->getSfd(), 5); // TODO: fix arbitrary
}

template <typename _AddrType>
std::unique_ptr<lsock::base::BaseSocketStream<_AddrType>>
lsock::base::BaseServer<_AddrType>::accept_basic()
{
    int sfd = accept(this->getSfd(), nullptr, nullptr);
    if (sfd < 0)
      return nullptr;

    std::unique_ptr<
      lsock::base::BaseSocketStream<_AddrType>
      > ptr(new lsock::base::BaseSocketStream<_AddrType>(sfd));

    return ptr;
}

template class lsock::base::BaseServer<struct sockaddr_in>;
template class lsock::base::BaseServer<struct sockaddr_un>;

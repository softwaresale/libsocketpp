
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
template <typename _RetType>
std::unique_ptr<_RetType>
lsock::base::BaseServer<_AddrType>::accepts()
{
    int sfd = accept(this->getSfd(), nullptr, nullptr);
    if (sfd < 0)
      return nullptr;
    
    std::unique_ptr<_RetType> ptr(new _RetType(sfd));

    return ptr;
}

template class lsock::base::BaseServer<struct sockaddr_in>;
template class lsock::base::BaseServer<struct sockaddr_un>;
template std::unique_ptr<lsock::base::BaseSocketStream<struct sockaddr_in>> 
	lsock::base::BaseServer<struct sockaddr_in>::accepts<lsock::base::BaseSocketStream<struct sockaddr_in>>();
template std::unique_ptr<lsock::base::BaseSocketStream<struct sockaddr_un>>
	lsock::base::BaseServer<struct sockaddr_un>::accepts<lsock::base::BaseSocketStream<struct sockaddr_un>>();
template std::unique_ptr<lsock::inet::TcpSocket>
	lsock::base::BaseServer<struct sockaddr_in>::accepts<lsock::inet::TcpSocket>();

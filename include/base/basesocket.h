
#ifndef _LS_BASE_SOCKET_H
# define _LS_BASE_SOCKET_H

#include <functional>
#include <memory>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

#include "addr.h"

namespace lsock
{
namespace base
{
    struct Connect
    {
    public:
	Connect() { }
	int operator()(int sock, struct sockaddr *addr, socklen_t size)
	    { return connect(sock, addr, size); }
	
    private:
    };

    struct Bind
    {
    public:
	Bind() { }
	int operator()(int sock, struct sockaddr *addr, socklen_t size)
	    { return bind(sock, addr, size); }
    };
  
    template <typename _ConnectFunc, typename _AddrType>
    class BaseSocket
    {
    public:
	BaseSocket() = delete;
	BaseSocket(int family, int type, int proto = 0);
	BaseSocket(int sfd);
	virtual ~BaseSocket();

        bool isOpen() { return (m_sockfd != -1); }
	int getSfd() const { return m_sockfd; }

	int connects(lsock::base::BaseSockAddr<_AddrType> *addr);

	ssize_t simple_write(char *data, size_t len, int flags = 0);
	ssize_t simple_read(char *data, size_t len, int flags = 0);

	void disconnect();
	
    protected:
	int m_sockfd;
	_ConnectFunc m_connector;
	
    };
}
}

#endif // _LS_BASE_SOCKET_H

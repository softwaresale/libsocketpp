
#ifndef _LS_INET_SOCKET_H
# define _LS_INET_SOCKET_H

#include <iostream>
#include <memory>
#include <functional>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../base/addr.h"
#include "../base/basesocket.h"
#include "../base/basesockstream.h"

namespace lsock
{
namespace inet
{

    class TcpSocket : public lsock::base::BaseSocketStream<struct sockaddr_in>
    {
    public:
	TcpSocket()
	    : lsock::base::BaseSocketStream<struct sockaddr_in>(AF_INET, SOCK_STREAM, 0)
	    { }
	
	TcpSocket(int sfd)
	    : lsock::base::BaseSocketStream<struct sockaddr_in>(sfd)
	    { }
	
	virtual ~TcpSocket()
	    { }
    };
  
}
}

#endif 

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
    namespace tcp
    {
        class Socket : public lsock::base::SocketStream<struct sockaddr_in>
        {
        public:
            Socket()
                : lsock::base::SocketStream<struct sockaddr_in>(AF_INET, SOCK_STREAM, 0)
                { }

            Socket(int sfd)
                : lsock::base::SocketStream<struct sockaddr_in>(sfd)
                { }

            virtual ~Socket()
                { disconnect(); }

        };
    }
}

#endif

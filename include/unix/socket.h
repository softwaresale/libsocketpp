
#ifndef _LS_UNIX_SOCKET_H
# define _LS_UNIX_SOCKET_H

#include "../base/basesocket.h"
#include "../base/basesockstream.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

namespace lsock
{
    namespace ux
    {

        class Socket : public lsock::base::SocketStream<struct sockaddr_un>
        {
        public:
            Socket()
                : lsock::base::SocketStream<struct sockaddr_un>(AF_UNIX, SOCK_STREAM, 0)
                { }

            Socket(int sfd)
                : lsock::base::SocketStream<struct sockaddr_un>(sfd)
                { }

            virtual ~Socket()
                { disconnect(); }
        };
    }
}

#endif

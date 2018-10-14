
#ifndef _LS_UNIX_SERVER_H
# define _LS_UNIX_SERVER_H

#include "../base/baseserver.h"
#include "socket.h"
#include <sys/un.h>

namespace lsock
{
    namespace ux
    {

        class Server : public lsock::base::Server<struct sockaddr_un>
        {
        public:
            Server()
                : lsock::base::Server<struct sockaddr_un>(AF_UNIX, SOCK_STREAM, 0)
                { }

            Server(int sfd)
                : lsock::base::Server<struct sockaddr_un>(sfd)
                { }

            virtual ~Server()
                { disconnect(); }

            std::unique_ptr<lsock::ux::Socket> accept()
                {
                    std::unique_ptr<lsock::base::SocketStream<struct sockaddr_un>> bptr = accept_basic();
                    lsock::base::SocketStream<struct sockaddr_un> *rawptr = bptr.release();
                    std::unique_ptr<lsock::ux::Socket> retptr(static_cast<lsock::ux::Socket*>(rawptr));

                    return retptr;
                }
        };

    }
}

#endif // _LS_UNIX_SERVER_H


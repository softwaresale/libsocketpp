
#ifndef _LS_INET_TCPSERVER_H
# define _LS_INET_TCPSERVER_H

#include "../base/basesocket.h"
#include "../base/basesockstream.h"
#include "../base/baseserver.h"
#include "socket.h"
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <memory>

namespace lsock
{
    namespace tcp
    {
        class Server : public lsock::base::Server<struct sockaddr_in>
        {
        public:
            Server()
                : lsock::base::Server<struct sockaddr_in>(AF_INET, SOCK_STREAM, 0)
                { }

            Server(int sfd)
                : lsock::base::Server<struct sockaddr_in>(sfd)
                { }

            virtual ~Server()
                { }

            std::unique_ptr<lsock::tcp::Socket> accept()
                {
                    std::unique_ptr<lsock::base::SocketStream<struct sockaddr_in>> fptr = accept_basic();
                    lsock::base::SocketStream<struct sockaddr_in> *raw_ptr = fptr.release();
                    std::unique_ptr<lsock::tcp::Socket> sockptr(static_cast<lsock::tcp::Socket*>(raw_ptr));

                    return sockptr;
                }
        };
    }
}

#endif // _LS_INET_TCPSERVER_H

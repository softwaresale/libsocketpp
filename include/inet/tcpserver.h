
#ifndef _LS_INET_TCPSERVER_H
# define _LS_INET_TCPSERVER_H

#include "../base/basesocket.h"
#include "../base/basesockstream.h"
#include "../base/baseserver.h"
#include "tcpsocket.h"
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <memory>

namespace lsock
{
    namespace inet
    {
        class TcpServer : public lsock::base::BaseServer<struct sockaddr_in>
        {
        public:
            TcpServer()
                : lsock::base::BaseServer<struct sockaddr_in>(AF_INET, SOCK_STREAM, 0)
                { }

            TcpServer(int sfd)
                : lsock::base::BaseServer<struct sockaddr_in>(sfd)
                { }

            virtual ~TcpServer()
                { }

            std::unique_ptr<TcpSocket> accept()
                {
                    std::unique_ptr<lsock::base::BaseSocketStream<struct sockaddr_in>> fptr = accept_basic();
                    lsock::base::BaseSocketStream<struct sockaddr_in> *raw_ptr = fptr.release();
                    std::unique_ptr<TcpSocket> sockptr(static_cast<TcpSocket*>(raw_ptr));

                    return sockptr;
                }
        };
    }
}

#endif // _LS_INET_TCPSERVER_H

#ifndef _LS_BASE_SOCK_STREAM_H
# define _LS_BASE_SOCK_STREAM_H

#include "basesocket.h"
#include "basesockbuf.h"
#include <iostream>
#include <netinet/in.h>
#include <sys/un.h>

namespace lsock
{
    namespace base
    {
        template <typename _AddrType>
        class SocketStream : public Socket<Connect, _AddrType>, public std::iostream
        {
        public:
            SocketStream() = delete;
            SocketStream(int family, int type, int proto = 0)
                : Socket<Connect, _AddrType>(family, type, proto),
                  std::iostream(new SocketBuf<_AddrType>(this))
                {
                }

            SocketStream(int sfd)
                : Socket<Connect, _AddrType>(sfd),
                  std::iostream(new SocketBuf<_AddrType>(this))
                {
                }

            virtual ~SocketStream()
                { }
        };

        template class SocketStream<struct sockaddr_in>;
        template class SocketStream<struct sockaddr_un>;
    }
}

#endif

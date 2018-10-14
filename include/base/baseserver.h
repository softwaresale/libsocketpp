#ifndef _LS_BASE_SERVER_H
# define _LS_BASE_SERVER_H

#include <memory>
#include <sys/types.h>
#include "basesocket.h"
#include "basesockstream.h"
#include "addr.h"

namespace lsock
{
    namespace base
    {
        template <typename _AddrType>
        class Server : public Socket<Bind, _AddrType>
        {
        public:
            Server() = delete;
            Server(int family, int type, int proto = 0);
            Server(int sfd);
            virtual ~Server();

            int connect(SockAddr<_AddrType> *addr);

            std::unique_ptr<SocketStream<_AddrType>> accept_basic();

            ssize_t simple_read(char *, size_t, int) = delete;
            ssize_t simple_write(char *, size_t, int) = delete;
        };

    }
}

#endif // _LS_BASE_SERVER_H

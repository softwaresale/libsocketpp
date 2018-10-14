
#ifndef _LS_UNIX_ADDR_H
# define _LS_UNIX_ADDR_H

#include <string>
#include "../base/addr.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

namespace lsock
{
#if 1
    namespace ux
    {
#endif
        class Addr : public lsock::base::SockAddr<struct sockaddr_un>
        {
        public:
            enum Type {
                NORMAL,
                ABSTRACT
            };

            Addr();
            Addr(const std::string &path, Type type = NORMAL);
            virtual ~Addr();

            void set(const std::string &path, Type type = NORMAL);
        };
#if 1
    }
#endif
}

#endif // _LS_UNIX_ADDR_H

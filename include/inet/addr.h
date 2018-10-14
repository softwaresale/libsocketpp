
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../base/addr.h"

namespace lsock
{
    namespace inet
    {
        class Addr : public lsock::base::SockAddr<struct sockaddr_in>
        {
        public:
            Addr();
            Addr(const std::string &name, int port);
            virtual ~Addr();

            void setHost(const std::string &name);
            void setPort(int port);
            void set(const std::string &name, int port);
        };
    }
}

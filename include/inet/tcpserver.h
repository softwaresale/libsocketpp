
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
    };
}
}

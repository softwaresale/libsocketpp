
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../base/addr.h"

namespace lsock
{
namespace inet
{

    class InetAddr : public lsock::base::BaseSockAddr<struct sockaddr_in>
    {
    public:
	InetAddr();
	InetAddr(const std::string &name, int port);
	virtual ~InetAddr();

	void setHost(const std::string &name);
	void setPort(int port);
	void set(const std::string &name, int port);
    };
}
}

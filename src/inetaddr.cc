
#include <string>
#include <netinet/in.h>
#include <base/addr.h>
#include <inet/addr.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

lsock::inet::InetAddr::InetAddr()
    : lsock::base::BaseSockAddr<struct sockaddr_in>()
{ }

lsock::inet::InetAddr::InetAddr(const std::string &host, int port)
    : lsock::base::BaseSockAddr<struct sockaddr_in>()
{
    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(port);
    if (host == "default-host") {
	m_addr.sin_addr.s_addr = INADDR_ANY;
    } else {
	inet_pton(AF_INET, host.c_str(), &m_addr.sin_addr);
    }
}

lsock::inet::InetAddr::~InetAddr()
{
}

void
lsock::inet::InetAddr::setHost(const std::string &host)
{
    if (host == "default-host") {
	m_addr.sin_addr.s_addr = INADDR_ANY;
    } else {
	inet_pton(AF_INET, host.c_str(), &m_addr.sin_addr);
    }
}

void
lsock::inet::InetAddr::setPort(int port)
{
    m_addr.sin_port = htons(port);
}

void
lsock::inet::InetAddr::set(const std::string &host, int port)
{
    setHost(host);
    setPort(port);
}


#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/un.h>
#include <base/addr.h>
#include <unix/addr.h>

lsock::ux::Addr::Addr()
    : lsock::base::SockAddr<struct sockaddr_un>()
{
    m_addr.sun_family = AF_UNIX;
}

lsock::ux::Addr::Addr(const std::string& path, lsock::ux::Addr::Type type)
    : lsock::base::SockAddr<struct sockaddr_un>()
{
    if (type == ABSTRACT) {

        *m_addr.sun_path = '\0';
        const char *data = path.c_str();
        strncpy(m_addr.sun_path + 1, data, sizeof(m_addr.sun_path) - 2);

    } else {
        path.copy(m_addr.sun_path, path.length());
    }
}

lsock::ux::Addr::~Addr()
{ }

void
lsock::ux::Addr::set(const std::string &path, Type type)
{
    if (type == ABSTRACT) {

        *m_addr.sun_path = '\0';
        const char *data = path.c_str();
        strncpy(m_addr.sun_path + 1, data, sizeof(m_addr.sun_path) - 2);

    } else {
        path.copy(m_addr.sun_path, path.length());
    }
}

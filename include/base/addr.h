#ifndef _LS_BASE_ADDR_H
# define _LS_BASE_ADDR_H

#include <string>
#include <sys/types.h>
#include <sys/socket.h>

namespace lsock
{
  namespace base
  {
    template <typename _Address>
    class BaseSockAddr
    {
    public:
      using Address = _Address;
      BaseSockAddr();
      virtual ~BaseSockAddr() { }

      virtual struct sockaddr *get();
      virtual socklen_t size();

    protected:
      Address m_addr;
    };
  }
}

#endif // _LS_BASE_ADDR_H

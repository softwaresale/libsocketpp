
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
    class BaseServer : public BaseSocket<Bind, _AddrType>
    {
    public:
	BaseServer() = delete;
	BaseServer(int family, int type, int proto = 0);
	BaseServer(int sfd);
	virtual ~BaseServer();

	template <typename _RetType>
	std::unique_ptr<_RetType> accepts();
	
	ssize_t simple_read(char *, size_t, int) = delete;
	ssize_t simple_write(char *, size_t, int) = delete;
    };

}
}

#endif // _LS_BASE_SERVER_H


#ifndef _LS_BASE_SOCK_STREAM_H
# define _LS_BASE_SOCK_STREAM_H

#include "basesocket.h"
#include "basesockbuf.h"
#include <iostream>

namespace lsock
{
namespace base
{
    template <typename _AddrType>
    class BaseSocketStream : public BaseSocket<Connect, _AddrType>, public std::iostream
    {
    public:
	BaseSocketStream() = delete;
	BaseSocketStream(int family, int type, int proto = 0)
	    : BaseSocket<Connect, _AddrType>(family, type, proto),
	    std::iostream(new BaseSocketBuf<_AddrType>(this))
	    {

	    }

	BaseSocketStream(int sfd)
	    : BaseSocket<Connect, _AddrType>(sfd),
	    std::iostream(new BaseSocketBuf<_AddrType>(this))
	    {
		
	    }

	virtual ~BaseSocketStream()
	    { }
    };
}
}

#endif


/*
  Header for basesockbuf

  Copyright (C) 2017  Charlie Sale

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BASESOCKBUF_H
#define BASESOCKBUF_H 1

#include "basesocket.h"
#include <streambuf>
#include <vector>
#include <memory>
#include <sys/types.h>
#include <sys/socket.h>

namespace lsock
{
namespace base
{
    template <typename _AddrType>
    class BaseSocketBuf : public std::streambuf
    {

    private:
	std::shared_ptr<lsock::base::BaseSocket<Connect, _AddrType>> m_sock;  // internal socket
	std::vector<char> m_in_buffer; // internal character buffer?
	std::vector<char> m_out_buffer; // buffer for writing outwards
	// const size_t  putback; // put back size

	// hide copy and assignment
	BaseSocketBuf(const BaseSocketBuf &);
	BaseSocketBuf &operator=(const BaseSocketBuf &);

    protected:
	int_type overflow(char ch);
	int_type underflow();
	int sync();

    public:
	BaseSocketBuf(BaseSocket<Connect, _AddrType> *_sock);
    };
}
}

#endif // BASESOCKBUF_H

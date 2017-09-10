
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

#include <streambuf>
#include <socketpp/tcp/basesocket.h>
#include <vector>

using namespace std;

namespace socketpp::tcp
{

class base_sock_buf : public streambuf
{

private:
  basic_socket* sock;    // internal socket
	vector<char>  buffer;  // internal character buffer?
	vector<char>  outBuf; // buffer for writing outwards
	//const size_t  putback; // put back size

	// hide copy and assignment
	base_sock_buf(const base_sock_buf&);
	base_sock_buf& operator=(const base_sock_buf&);

protected:
	int_type overflow(char ch);
	int_type underflow();
	int sync();

public:
	base_sock_buf(basic_socket* _sock);

};

}

#endif // BASESOCKBUF_H

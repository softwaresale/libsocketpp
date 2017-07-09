
/*
 Header for socket

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


#ifndef SOCKET_H
#define SOCKET_H 1

#include <socketpp/tcp/basesocket.h>
#include <iostream>
#include <socketpp/tcp/basesockbuf.h>
#include <ostream>

using namespace std;

namespace tcp
{

class Socket : public tcp::basic_socket, public iostream
{

private:

protected:

public:
	Socket();
	Socket(const char*, int);
	Socket(int);



};
	
};

ostream& send(ostream& out);

#endif // SOCKET_H

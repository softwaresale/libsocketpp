
/*
  This is one of the main classes generated from libsocketpp. It is a 
  streambases TCP socket class.


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

#include <socketpp/tcp/basesocket.h>
#include <socketpp/tcp/socket.h>
#include <iostream>
#include <socketpp/tcp/basesockbuf.h>
#include <netinet/in.h>
#include <cstdint>
#include <cstring>
#include <sstream>

using namespace std;

/* The Socket class is really just an amalgum
* of the various base classes. It inherits basic_socket
* and iostream directly and uses base_sock_buf as a
* supporting class */
tcp::Socket::Socket()
	: basic_socket(),
	  iostream(new base_sock_buf(this))
	  /* Using the already instantiated basic_socket part of self */
{

}

tcp::Socket::Socket(const char* host, int port)
	: basic_socket(host, port),
	  iostream(new base_sock_buf(this))
{

}

tcp::Socket::Socket(int sockfd)
	: basic_socket(sockfd),
	  iostream(new base_sock_buf(this))
{

}

ostream&
tcp::Socket::operator<<(int val)
{
	int32_t conv = htonl(val);
	char* data = (char*) &conv;
	int size = sizeof(conv);

	this->write(data, size);

	return *this;
}

ostream&
tcp::Socket::operator<<(double val)
{
	ostringstream str;

	str << val;

	string _str = str.str();
	const char* buf = _str.c_str();

	this->write(buf, strlen(buf));

	return *this;
}

ostream&
tcp::Socket::operator<<(float val)
{
	ostringstream _str;
	_str << val;
	string str = _str.str();
	const char* buf = str.c_str();

	this->write(buf, strlen(buf));

	return *this;
}


istream&
tcp::Socket::operator>>(int& val)
{
	int32_t ret;

	char* data = (char*) &ret;
	int left = sizeof(ret);

	this->read(data, left); // read the data

	val = ntohl(ret);

	return *this;
}

istream&
tcp::Socket::operator>>(double& val)
{
	char* buffer = new char[sizeof(double)];

	this->getline(buffer, sizeof(double)); // read double value into buffer

	val = atof(buffer); // try this...

	return *this;
}

istream&
tcp::Socket::operator>>(float& val)
{
	char* buffer = new char[sizeof(float)];
	this->getline(buffer, sizeof(float));

	val = atof(buffer);

	return *this;
}

ostream&
send(ostream& out)
{
	out << '\n';
	out.flush();
	return out;
}

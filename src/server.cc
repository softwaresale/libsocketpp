

/*
  This class is a basic TCP server that listens for connections
  and returns pointers to tcp::Socket classes upon connection.
  This connection is then used for communicating with the connection


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

#include "../include/socketpp/tcp/server.h"
#include "../include/socketpp/tcp/socket.h"
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

/* This is a basic all around tcp server */

tcp::Server::Server() {

  // creates the server socket
  server = socket(AF_INET, SOCK_STREAM, 0);
  if (server < 0) {
    cerr << "server.cc:Server ctor: Error creating listening socket" << endl;
  }
}

tcp::Server::Server(int _port) {

  // creates the socket
  server = socket(AF_INET, SOCK_STREAM, 0);
  if (server < 0) {
    cerr << "Error creating listening socket" << endl;
  }

  // sets local variables
  port = _port;
}

int tcp::Server::binds() {

  if (_isBound) {
    cerr << "Server already bound" << endl;
    return 1;
  }

  // set up the address
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(server, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    cerr << "Error listening socket" << endl;
    return 1;
  }

  _isBound = true; // socket has been bound

  return 0;
}

int tcp::Server::binds(int _port) {

  if (_isBound) {
    cerr << "Server already bound" << endl;
    return 1;
  }

  // set up the address
  addr.sin_family = AF_INET;
  addr.sin_port = htons(_port);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(server, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    cerr << "Error listening socket" << endl;
    return 1;
  }

  _isBound = true; // server has been bound

  return 0;
}

bool tcp::Server::isBound() { return this->_isBound; }

int tcp::Server::setKeepAlive(bool var) {
  int _var = (int)var;
  return setsockopt(this->server, SOL_SOCKET, SO_KEEPALIVE, &_var, sizeof(int));
}

int tcp::Server::isKeepAlive() {
  int status = 0;
  socklen_t len = (socklen_t)sizeof(status);
  int ret =
      getsockopt(this->server, SOL_SOCKET, SO_KEEPALIVE, (void *)&status, &len);
  if (ret == -1)
    return ret;
  else
    return status; // should be flag
}

int tcp::Server::setReuseAddr(bool var) {
  int _var = (int)var;
  return setsockopt(this->server, SOL_SOCKET, SO_REUSEADDR, &_var, sizeof(int));
}

int tcp::Server::isReuseAddr() {
  int val = 0;
  socklen_t len = (socklen_t)sizeof(val);
  int ret =
      getsockopt(this->server, SOL_SOCKET, SO_REUSEADDR, (void *)&val, &len);
  if (ret == -1)
    return ret;
  else
    return val;
}

tcp::Socket &tcp::Server::accepts() {

  listen(server, 10); // sets the server to listen
  conn = accept(server, (struct sockaddr *)NULL, NULL);
  if (conn < 0) {
    cerr << "Error accepting connection" << endl;
    // TODO: handle error
  }

  tcp::Socket *temp = new tcp::Socket(conn);

  return *temp;
}

int tcp::Server::acceptfd() {

  listen(server, 10); // sets the server to listen
  conn = accept(server, (struct sockaddr *)NULL, NULL);
  if (conn < 0) {
    cerr << "Error accepting connection" << endl;
    return 0;
  }

  return conn; // you actually have to return the value
}

void tcp::Server::closes() {
  close(conn);
  close(server);
}

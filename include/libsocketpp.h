
#ifndef _LS_H
# define _LS_H

#include <libsocketpp/base/basesocket.h>
#include <libsocketpp/base/basesockbuf.h>
#include <libsocketpp/base/basesockstream.h>
#include <libsocketpp/base/addr.h>
#include <libsocketpp/inet/addr.h>
#include <libsocketpp/tcp/socket.h>
#include <libsocketpp/tcp/server.h>
#include <libsocketpp/unix/server.h>
#include <libsocketpp/unix/socket.h>
#include <libsocketpp/unix/addr.h>

namespace lsock
{
    using TcpSocket = lsock::tcp::Socket;
    using TcpServer = lsock::tcp::Server;

    using InetAddr  = lsock::inet::Addr;

    using UnixSocket = lsock::unix::Socket;
    using UnixServer = lsock::unix::Server;
    using UnixAddr   = lsock::unix::Addr;
}

#endif // _LS_H

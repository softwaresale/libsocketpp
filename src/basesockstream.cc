
#include <socketpp/tcp/basesockstream.h>
#include <socketpp/tcp/basesocket.h>
#include <socketpp/tcp/basesockbuf.h>
#include <ostream>
#include <iostream>

using namespace std;

/*
tcp::Basic_Sockstream::Basic_Sockstream()
	: ostream(),
	  istream()
{
	
}
*/


tcp::Basic_Sockstream::Basic_Sockstream(Basic_Sockbuf* sockbuf) /* Sockbuf inherits streambuf */
	: iostream(sockbuf)
{
	this->internalSockbuf = sockbuf; // set the internal socket buffer
}



#include <tcp/basesockstream.h>
#include <tcp/basesocket.h>
#include <tcp/basesockbuf.h>
#include <ostream>

using namespace std;

tcp::Basic_Sockstream::Basic_Sockstream()
	: ostream()
{
	
}

tcp::Basic_Sockstream::Basic_Sockstream(Basic_Sockbuf* sockbuf)
	: ostream(sockbuf)
{
	this->internalSockbuf = sockbuf; // set the internal socket buffer
}


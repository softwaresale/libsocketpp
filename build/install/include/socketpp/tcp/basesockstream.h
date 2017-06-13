
/* This class is a stream for input and output with sockets */

#ifndef SOCKSTREAM_H
#define SOCKSTREAM_H 1

#include <ostream>
#include <istream>
#include <streambuf>
#include <iostream>
#include <tcp/basesockbuf.h>
#include <tcp/basesocket.h>

using namespace std;

namespace tcp
{

class Basic_Sockstream : public ostream,
			 public Basic_Sockbuf
{
private:
	

protected:
	Basic_Sockbuf* internalSockbuf; // interal socket buffer
	
public:
	Basic_Sockstream();
	Basic_Sockstream(Basic_Sockbuf* sockbuf);
	
};

};

#endif // SOCKSTREAM_H

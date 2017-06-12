
/* This class is a stream for input and output with sockets */

#ifndef SOCKSTREAM_H
#define SOCKSTREAM_H 1

#include <ostream>
#include <istream>
#include <streambuf>
#include <iostream>
#include <tcp/basesockbuf.h>

using namespace std;

namespace tcp
{

template<class charT, class Traits=char_traits<charT>>
class Basic_SockStream : virtual public basic_ostream<charT, Traits>,
                   virtual public basic_istream<charT, Traits>
{

  private:
        Basic_Sockbuf* internalBuffer; // just in case  

  protected:

        template<class charT, class Traits=char_traits<charT>>
        friend basic_ostream<charT, Traits>& operator << (basic_ostream<charT, Traits> os, const char* buffer); // buffer to write
	friend basic_istream<charT, Traits>& operator >> (basic_istream<charT, Traits> is, const char* buffer); // buffer to read

  public:
	template<class charT, class Traits=char_traits<charT>>
	Basic_SockStream(Basic_Sockbuf<charT, Traits>* buffer); // opens a new socket stream on a socket buffer

	

};

};

#endif // SOCKSTREAM_H

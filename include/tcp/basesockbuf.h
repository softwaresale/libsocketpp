
/* This is a basic class for inheriting streambuf to make a socket class */

#ifndef BASIC_SOCKBUF_H
#define BASIC_SOCKBUF_H 1

#include <streambuf>

using namespace std;

namespace tcp
{

class Basic_Sockbuf
	: public streambuf
{

 private:
	char ch; // single byte for buffering
	
  
 protected:

	int underflow();
	int overflow(char ch);
	
 public:
	Basic_Sockbuf(); // creates a new streambuf

	
};
 
};

#endif // BASIC_SOCKBUF_H

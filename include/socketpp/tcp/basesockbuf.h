
/* This is a basic class for inheriting streambuf to make a socket class */

#ifndef BASIC_SOCKBUF_H
#define BASIC_SOCKBUF_H 1

#include <streambuf>
#include <socketpp/tcp/basesocket.h>
#include <vector>

using namespace std;

namespace tcp
{

class Basic_Sockbuf
	: public streambuf
{

 private:
	vector<char> buffer;
	size_t put_back;
	Basic_socket* sock;
	
 protected:
	virtual streambuf::int_type underflow();
	virtual streambuf::int_type overflow(char ch);
	virtual int sync();
	
 public:
	//Basic_Sockbuf();                      // creates a new streambuf with basic socket
	Basic_Sockbuf(Basic_socket*);
};
 
};

#endif // BASIC_SOCKBUF_H

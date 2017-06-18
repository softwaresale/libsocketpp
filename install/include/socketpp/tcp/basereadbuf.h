#ifndef BASESOCKIN_H
#define BASESOCKIN_H 1

#include <streambuf>
#include <socketpp/tcp/basesocket.h>
#include <vector>

using namespace std;

namespace tcp
{

class basic_read_buf : public streambuf
{

private:
	basic_socket* sock;    // internal socket
	vector<char>  buffer;  // internal character buffer?
	const size_t  putback; // put back size

	// hide copy and assignment
	basic_read_buf(const basic_read_buf&);
	basic_read_buf& operator=(const basic_read_buf&);
	
protected:
	int_type underflow();
	
public:
        basic_read_buf(basic_socket*);

};

};

#endif // BASESOCKIN_H

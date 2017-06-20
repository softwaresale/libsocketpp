
#ifndef BASESOCKBUF_H
#define BASESOCKBUF_H 1

#include <streambuf>
#include <socketpp/tcp/basesocket.h>
#include <vector>

using namespace std;

namespace tcp
{

class base_sock_buf : public streambuf
{

private:
        basic_socket* sock;    // internal socket
	vector<char>  buffer;  // internal character buffer?
	//const size_t  putback; // put back size

	// hide copy and assignment
	base_sock_buf(const base_sock_buf&);
	base_sock_buf& operator=(const base_sock_buf&);

protected:
	int_type overflow(char ch);
	int_type underflow();
	int sync();
	
public:
	base_sock_buf(basic_socket* _sock);
	
};

};

#endif // BASESOCKBUF_H


#ifndef BASESOCKOUT_H
#define BASESOCKOUT_H 1

#include <socketpp/tcp/basesocket.h>
#include <streambuf>
#include <vector>

using namespace std;

namespace tcp
{

class basic_write_buf : public streambuf
{

private:
	vector<char> buffer; // internal buffer
	basic_socket* sock; // internal socket

	// privatize copy constructors
	basic_write_buf(const basic_write_buf&);
	basic_write_buf& operator=(const basic_write_buf&);
	
protected:
	int_type overflow(char ch);
	int      sync();
	
public:
	basic_write_buf(basic_socket* _sock);
	
};

};

#endif // BASESOCKOUT_H
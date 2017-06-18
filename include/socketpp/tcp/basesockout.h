
#ifndef BASESOCKOUT_H
#define BASESOCKOUT_H 1

#include <ostream>
#include <socketpp/tcp/basesocket.h>
#include <socketpp/tcp/basewritebuf.h>
#include <streambuf>

using namespace std;

namespace tcp
{

class base_sock_output : public ostream
{

private:
	
protected:
	
public:
	base_sock_output(base_write_buf* buffer);
	
};

};

#endif // BASESOCKOUT_H

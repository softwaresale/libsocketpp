
#ifndef BASESOCKIN_H
#define BASESOCKIN_H 1

#include <socketpp/tcp/basereadbuf.h>
#include <istream>
#include <streambuf>

using namespace std;

namespace tcp
{

class base_sock_input : public istream
{

private:

protected:

public:
	base_sock_input(base_read_buf*);

};

};

#endif // BASESOCKIN_H

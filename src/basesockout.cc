
#include <socketpp/tcp/basesockout.h>
#include <ostream>
#include <streambuf>
#include <socketpp/tcp/basewritebuf.h>

using namespace std;

tcp::base_sock_output::base_sock_output(base_write_buf* buf)
	: ostream(buf)
{	
}

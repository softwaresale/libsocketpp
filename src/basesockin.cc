
#include <socketpp/tcp/basesockin.h>
#include <socketpp/tcp/basereadbuf.h>
#include <istream>
#include <streambuf>

using namespace std;

tcp::base_sock_input::base_sock_input(base_read_buf* buf)
	: istream(buf)
{
}

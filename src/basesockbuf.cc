
#include <tcp/basesockbuf.h>
#include <streambuf>
#include <cstdlib>

using namespace std;

tcp::Basic_Sockbuf::Basic_Sockbuf()
	: streambuf ()
{
	// Creates a sockbuf, need to see what happens and how this works
}

int
tcp::Basic_Sockbuf::overflow(char ch)
{
	if (ch != EOF){
		
	}
}

int
tcp::Basic_Sockbuf::underflow()
{
	char ch;
	while ((ch = this->sbumpc()));
	this->setg(&ch, &ch, &ch+1);
	return ch;
}



// Give this a shot

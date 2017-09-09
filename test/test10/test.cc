
#include <socketpp/http/httpresponse.h>
#include <socketpp/http/httprequest.h>
#include <socketpp/http/httpbase.h>
#include <iostream>

using namespace std;
using namespace socketpp::http;

int main()
{
	http_request req("GET /home/index.html HTTP/1.1");

	cout << req.toString() << endl;

  http_request parsed_request;

  parsed_request.parse("POST /home/update.html HTTP/1.1");

	return 0;
}

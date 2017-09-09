
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
	
	cout << "Making oreq..." << endl;
        http_request oreq;
	cout << "Made" << endl;
	
	cout << "Setting options..." << endl;
	oreq.setCmd(POST);
	oreq.setURI("/home/index.html");

	cout << oreq.toString() << endl;

	return 0;
}

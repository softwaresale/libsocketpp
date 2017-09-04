
#include <iostream>
#include <socketpp/http/httpbase.h>
#include <socketpp/http/httpresponse.h>
#include <sstream>
#include <vector>
#include <utility>
#include <string>

using namespace std;

http::http_response::http_response()
  : http::http_base()
{
    this->setCmdData("version", "HTTP/1.1");
}

http::http_response::http_response(string _data)
  : http::http_base(_data)
{
    this->setCmdData("version", "HTTP/1.1");
}

void
http::http_response::setStatusCode(int data)
{
    ostringstream num;
    num << data;
    this->setCmdData("status", num.str());
}

int
http::http_response::getStatusCode()
{
    string str = this->cmd_line[1];
    return stoi(str);
}

void
http::http_response::setStatusText(string stat)
{
    this->setCmdData("text", stat);
}

string
http::http_response::getStatusText()
{
    return this->cmd_line[2];
}

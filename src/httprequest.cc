
#include <sstream>
#include <iostream>
#include <socketpp/http/httpbase.h>
#include <socketpp/http/httprequest.h>

using namespace std;

http::http_request::http_request()
{
    this->setCmdData("_version", "HTTP/1.1");
}

http::http_request::http_request(string request)
{
    
}

void
http::http_request::setCmd(http_cmd_t cmd)
{
    string cmd;
    switch (cmd){
    case GET:
        cmd = "GET";
        break;

    case POST:
        cmd = "POST";
        break;

    case HEAD:
        cmd = "HEAD";
        break;

    case PUT:
        cmd = "PUT";
        break;

    case DELETE:
        cmd = "DELETE";
        break;

    case CONNECT:
        cmd = "CONNECT";
        break;

    case OPTIONS:
        cmd = "OPTIONS";
        break;

    case TRACE:
        cmd = "TRACE";
        break;

    default:
        break;
    }

    this->setCmdData("command", cmd);
}

void
http::http_request::setURI(string uri)
{
    this->setCmdData("uri", uri);
}


#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
#include <socketpp/http/httpbase.h>
#include <sstream>

using namespace std;

http::http_base::http_base()
{
}

void
http::http_base::setBody(string data)
{
    this->body = data;
}

string
http::http_base::dumpBody()
{
    return this->body;
}

void
http::http_base::setCmdData(string key, string val)
{
    if (key == "command" || key == "version")
        this->body.insert(0, val);
    else if (key == "uri" || key == "status")
        this->body.insert(1, val);
    else if (key == "_version" || key == "text")
        this->body.insert(2, val);
}

string
http::http_base::dumpCmd()
{
    vector<string>::iterator it;

    ostringstream str;

    for (it  = cmd_line.begin();
         it != cmd_line.end();
         it++){

        string st = *it;
        str << st << " ";
    }
    str << "\n";

    return str.str();
}

void
http::http_base::setHeaderData(string key, string value)
{
    this->header_data.push_back({key, value});
}

void
http::http_base::dumpHead()
{

    vector<pair<string, string>>::iterator it;
    ostringstream str;

    for (it  = header_data.begin();
         it != header_data.end();
         it++){

        pair<string, string> item = *it;
        str << item.first << ": " << item.second << "\n";
    }

    return str.str();
}





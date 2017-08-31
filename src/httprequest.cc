
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
    istringstream istr(request);

    char* cmdLine = new char[256]; // try to set a more dynamic value
    istr.getline(cmdLine, 256);
    string _cmd(cmdLine);

    if (_cmd != "HTTP/1.1") /* Not a response */ {

        // parse out data
        int ctr = 0;
        char c;

        istringstream cmd_parser(_cmd);

        ostringstring cmd, uri, version;

        // get command
        char* __cmd = new char[12];
        cmd_parser.get(cmd, 12, ' '); // deliminate at space
        cmd << __cmd;

        // get URI
        char* __uri = new char[256];
        cmd_parser.get(__uri, 256, ' '); // get at space
        uri << __uri;

        // get version
        char* __vers = new char[strlen("HTTP/1.1")]; // too lazy to count
        cmd_parser.get(__vers, strlen("HTTP/1.1"), '\n'); // newline as delimator
        version << __vers;

        // insert all parts of command line into the vector
        this->cmd_line.insert(0, cmd.str());
        this->cmd_line.insert(1, uri.str());
        this->cmd_line.insert(2, version.str());

    } else {
        cerr << "REEEEE!!" << endl;
    }

    // get header data
    char* header = new char[256];
    istr.get(header, 256, "\n\n"); // at double new line
    string _hdr(header); // data contained in header
    istringstream hd(_hdr);

    // parse header data
    char* hdline = new char[64];
    while (hd.getline(hdline, 64)){
        istringstream item_parse(string(hdline));
        char* key = new char[32];
        char* val = new char[32];

        // read both values
        item_parse.get(key, 32, ': ');
        item_parse.get(val, 32, '\n');

        this->header_data.emplace_back({key, val}); // emplace a new element at the back
    }

    // all header data should be added

    char* _body = new char[256];
    isr.get(_body, 256, CRLF); // get until CRLF
    this->body = string(_body);


    // everything parsed
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

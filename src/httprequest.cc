

/*
  This is the class for creating http requests

  Copyright (C) 2017  Charlie Sale

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <sstream>
#include <iostream>
#include <socketpp/http/httpbase.h>
#include <socketpp/http/httprequest.h>

using namespace std;

static string
__commands[8] = {
    "GET",
    "POST",
    "HEAD",
    "PUT",
    "DELETE",
    "CONNECT",
    "OPTIONS",
    "TRACE"
  };

socketpp::http::http_request::http_request()
    : socketpp::http::http_base()
{
    this->setCmdData("_version", "HTTP/1.1");
}

socketpp::http::http_request::http_request(string request)
    : socketpp::http::http_base(request)
{
    // skip all of this parsing that probably wont work anyways
    /*
    istringstream istr(request);

    char* cmdLine = new char[256]; // try to set a more dynamic value
    istr.getline(cmdLine, 256);
    string _cmd(cmdLine);

    istringstream type(_cmd);
    char* header_type = new char[16];
    type.get(header_type, 16, " ");

    if (string(header_type) != "HTTP/1.1") /* Not a response  {

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

    } else {
        cerr << "REEEEE!!" << endl;
    }


    // everything parsed
    */
}

void
socketpp::http::http_request::setCmd(http_cmd_t cmd)
{
    string _cmd;

    _cmd = __commands[cmd];

    this->setCmdData("command", _cmd);
}

void
socketpp::http::http_request::setURI(string uri)
{
    this->setCmdData("uri", uri);
}



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
#include <cstring>
#include <utility>

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
}

int
socketpp::http::http_request::parse(string data)
{

  istringstream whole_response(data);

  // get first line
  char* __cmd_line = new char[64];
  whole_response.getline(__cmd_line, 64);
  __cmd_line[strlen(__cmd_line) + 1] = '\0';
  istringstream cmd_line(__cmd_line);

  // get header data
  char* __header_line = new char[128];
  ostringstream __header_data;
  while (whole_response.getline(__header_line, 128)){
    __header_data << __header_line;
  }
  istringstream header_data_str(__header_data.str());
  delete[] __header_line;

  // get body
  char* __line = new char[128];
  ostringstream __body;

  while (whole_response.getline(__line, 128)){
    __body << __line;
  }

  delete[] __line;

  this->body = __body.str();
  // parse data

  // get the version and make sure that data is not request
  char* command_buffer = new char[16];
  cmd_line.get(command_buffer, 16, ' '); // get first word
  if (string(command_buffer) != "HTTP/1.1"){

    // save version
    this->setCmdData("command", string(command_buffer));

    // get other parts of command line

    /// get uri
    char* uri = new char[128];
    cmd_line.get(uri, ' '); // get characters of uri
    this->setCmdData("uri", string(uri)); // double check this

    // get version
    char* version = new char[strlen("HTTP/1.1")];
    cmd_line.get(version, '\n');
    this->setCmdData("_version", string(version));

    // everything is set
    delete[] uri;
    delete[] version;
    delete[] command_buffer;

  } else {
    return 1;
  }

  // parse out header data type pairs
  int isDone = 0;
  while (!isDone){

    // read key and value, make pair, store data
    char* __key = new char[64];
    char* __val = new char[64];

    if (header_data_str.eof())
      isDone = 1; // finished

    header_data_str.get(__key, 64, ':');
    header_data_str.get(__val, 64, '\n');

    pair<string, string> value;
    value.first = string(__key);
    value.second = string(__val);

    this->header_data.push_back(value);

    // clean up
    delete[] __key;
    delete[] __val;
  }

  // done

  return 0;
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

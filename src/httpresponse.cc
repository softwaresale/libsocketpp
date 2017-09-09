

/*
  This class is used for generating HTTP responses

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


#include <iostream>
#include <socketpp/http/httpbase.h>
#include <socketpp/http/httpresponse.h>
#include <sstream>
#include <vector>
#include <utility>
#include <string>
#include <cstring>

using namespace std;

socketpp::http::http_response::http_response()
  : socketpp::http::http_base()
{
    this->setCmdData("version", "HTTP/1.1");
}

socketpp::http::http_response::http_response(string _data)
  : socketpp::http::http_base(_data)
{
    this->setCmdData("version", "HTTP/1.1");
}

int
socketpp::http::http_response::parse(string data)
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

  this->body = __body.str();

  // parse data

  // get the version and make sure that data is not request
  char* version_buffer = new char[16];
  cmd_line.get(version_buffer, 16, ' '); // get first word
  if (string(version_buffer) == "HTTP/1.1"){

    // save version
    this->setCmdData("version", string(version_buffer));

    // get other parts of command line
    char* status = new char[16];
    cmd_line.get(status, 16, ' ');
    this->setCmdData("status", string(status));

    char* txt = new char[16];
    cmd_line.get(txt, 16, '\n');
    this->setCmdData("text", string(txt));

    delete[] version_buffer;
    delete[] status;
    delete[] txt;

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
socketpp::http::http_response::setStatusCode(int data)
{
  ostringstream num;
  num << data;
  this->setCmdData("status", num.str());
}

int
socketpp::http::http_response::getStatusCode()
{
  string str = this->getCmdItem("status");
  return stoi(str);
}

void
socketpp::http::http_response::setStatusText(string stat)
{
  this->setCmdData("text", stat);
}

string
socketpp::http::http_response::getStatusText()
{
  return this->getCmdItem("_version");
}

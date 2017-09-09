

/*
  This file is the base class for the http request/response system

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
#include <unordered_map>
#include <utility>
#include <vector>
#include <socketpp/http/httpbase.h>
#include <sstream>

using namespace std;

socketpp::http::http_base::http_base()
    : isDataSet(0)
{
}

socketpp::http::http_base::http_base(string _data)
    : isDataSet(1),
      data(_data)
{
}

void
socketpp::http::http_base::setBody(string data)
{
    this->body = data;
}

string
socketpp::http::http_base::dumpBody()
{
    return this->body;
}

void
socketpp::http::http_base::setCmdData(string key, string val)
{
    if (key == "command" || key == "version")
        this->body.insert(0, val);
    else if (key == "uri" || key == "status")
        this->body.insert(1, val);
    else if (key == "_version" || key == "text")
        this->body.insert(2, val);
}

string
socketpp::http::http_base::dumpCmd()
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
socketpp::http::http_base::setHeaderData(string key, string value)
{
    this->header_data.push_back({key, value});
}

string
socketpp::http::http_base::dumpHead()
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

string
socketpp::http::http_base::toString()
{
    if (isDataSet)
        return this->data;

    /*
    ostringstream str;

    // dump cmd line
    vector<string>::iterator cmdit;
    for (cmdit = cmd_line.begin();
         cmdit != cmd_line.end();
         cmdit++) {

        str << *cmdit << " "; // write each command and a space
    }

    str << "\n"; // write a new line

    // dump header
    vector<pair<string, string>>::iterator headit;
    for (headit =  header_data.begin();
         headit != header_data.end();
         headit++){

        pair<string, string> p = *headit;
        str << p.first << ": " << p.second << "\n";
    }

    str << "\n";

    // dump body
    str << this->body << "\r\n";
    */

    ostringstream str;
    str << this->dumpCmd();
    str << this->dumpHead();
    str << this->dumpBody();
    str << "\r\n";

    return str.str();
}

constexpr unsigned int
str2int(const char* str, int h = 0)
{
  return !str[h] ? 5381 : (str2int(str, h+1)*33) ^ str[h];
}

string
socketpp::http::http_base::getCmdItem(string data)
{
  string item;
  switch (str2int(data.c_str())) {

  case str2int("version"):
  case str2int("command"):
    item = this->cmd_line.at(0);
    break;

  case str2int("uri"):
  case str2int("status"):
    item = this->cmd_line.at(1);
    break;

  default:
    item = this->cmd_line.at(2);
    break;
  }

  return item;
}

string
socketpp::http::http_base::getHeaderVal(string key)
{

  vector<pair<string,string>>::iterator vect_it;

  for (vect_it = this->header_data.begin();
       vect_it != this->header_data.end();
       vect_it++){

    pair<string, string> item = *vect_it;

    if (item.first == key){
      return item.second;
    }

  }

  return "";
}

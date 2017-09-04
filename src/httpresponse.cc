

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
    string str = this->cmd_line[1];
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
    return this->cmd_line[2];
}

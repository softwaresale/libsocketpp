

/*
  header file for httprequest.cc

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


#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <socketpp/http/httpbase.h>
#include <vector>
#include <utility>
#include <unordered_map>

using namespace std;

namespace socketpp::http
{


  // enumeration of HTTP request commands
  typedef enum
    {
      GET = 0,
      POST = 1,
      HEAD = 2,
      PUT = 3,
      DELETE = 4,
      CONNECT = 5,
      OPTIONS = 6,
      TRACE = 7
    } http_cmd_t;


class http_request : public http_base
{

private:

protected:

public:
  http_request();
  http_request(string);

  int parse(string);

  void setCmd(http_cmd_t);
  void setURI(string);
};

}

#endif // HTTPREQUEST_H

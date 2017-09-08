

/*
  This file is the header for HTTP responses

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

#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <iostream>
#include <socketpp/http/httpbase.h>

using namespace std;

namespace socketpp::http
{

  class http_response : public socketpp::http::http_base
  {

  private:

  protected:

   public:
    http_response();
    http_response(string);
    http_response(string, int);

    int parse(string);

    void   setStatusText(string);
    string getStatusText();

    void setStatusCode(int);
    int  getStatusCode();

  };

}

#endif // HTTPRESPONSE_H

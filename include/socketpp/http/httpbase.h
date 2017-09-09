

/*
  Header file for httpbase.cc

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


#ifndef HTTPBASE_H
#define HTTPBASE_H

#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

namespace socketpp::http
{

class http_base
{

protected:

  // containers of data
  /*
    0 -- command or version
    1 -- URI     or status
    2 -- Version or text
  */
  vector<string>               cmd_line;
  vector<pair<string, string>> header_data;
  string                       body;

  // if string is passed, just return it
  int isDataSet;
  string data;

  // sets portions of data (key -> value)
  void setCmdData(string, string);
  // returns string portion of objects
  string dumpCmd();

  string getCmdItem(string); // get's one of the command line parts (see map above)
  string getHeaderVal(string); // get the value of one of the header values

public:
  http_base();
  http_base(string);

  string toString();

  void setHeaderData(string, string);
  void setBody(string);
  string dumpHead();
  string dumpBody();
};

}

#endif // HTTPBASE

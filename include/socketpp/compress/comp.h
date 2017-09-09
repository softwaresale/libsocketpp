


/*
  Header for comp.cc

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


#ifndef COMPRESS_H
#define COMPRESS_H

#include <zlib.h>
#include <socketpp/compress/basecmp.h>

using namespace std;

namespace socketpp::cmp
{

  class comp : public socketpp::cmp::base_compress
  {

  public:
    comp();
    comp(const char*);
    comp(char*);
    comp(string);

    char* dump(); // get the compressed data
  };

}

#endif // COMPRESS_H

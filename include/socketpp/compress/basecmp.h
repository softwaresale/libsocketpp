

/*
  Header for compress.cc

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

using namespace std;

namespace socketpp::cmp
{

  class base_compress
  {

  private:
    z_stream stream;
    char*    indata; // data to work on
    char*    dump; // operation output

  public:
    base_compress();
    base_compress(char*);
    base_compress(const char* data);
    base_compress(string);

    void destroy();

  };

}

#endif // COMPRESS_H

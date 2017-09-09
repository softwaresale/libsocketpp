


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


#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#include <zlib.h>
#include <socketpp/compress/basecmp.h>

using namespace std;

namespace socketpp::cmp
{

  class decomp : public socketpp::cmp::base_compress
  {

  private:
    char* pointer_to_out_data; // derefrence this to the given value

  public:
    decomp();
    decomp(char*);
    decomp(const char*);
    decomp(string);

    void inflate(char*);

  };

}

#endif // DECOMPRESS_H

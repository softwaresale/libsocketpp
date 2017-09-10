
/*
  This file handles data for compressing and decompressing data within
  sockets

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

#include <socketpp/compress/basecmp.h>
#include <zlib.h>
#include <iostream>
#include <sstream>

using namespace std;

/*
  This constructor chaining might not work...
 */

socketpp::cmp::base_compress::base_compress()
{
  // set up stream
  this->stream.zalloc = Z_NULL;
  this->stream.zfree  = Z_NULL;
  this->stream.opaque = Z_NULL;
}

socketpp::cmp::base_compress::base_compress(char* data)
  : socketpp::cmp::base_compress()
{
  this->indata    = data;
  this->dump_data = new char[sizeof(data)];
}

void
socketpp::cmp::base_compress::destroy()
{
  delete[] indata;
  delete[] dump_data;
}

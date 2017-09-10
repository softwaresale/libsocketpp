
/*
  This file handles compressing data for the socket

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
#include <socketpp/compress/comp.h>
#include <iostream>
#include <cstring>
#include <zlib.h>

using namespace std;

socketpp::cmp::comp::comp()
  : socketpp::cmp::base_compress()
{
}

socketpp::cmp::comp::comp(char* data)
  : socketpp::cmp::base_compress(data)
{
  // compress data
  stream.avail_in  = (uInt)   strlen(indata)+1; // size of input string and terminator
  stream.next_in   = (Bytef*) indata;
  stream.avail_out = (uInt)   sizeof(this->dump_data);
  stream.next_out  = (Bytef*) this->dump_data;

  deflateInit(&stream, Z_BEST_COMPRESSION);
  deflate(&stream, Z_FINISH);
  deflateEnd(&stream);
}

socketpp::cmp::comp::comp(const char* data)
  : socketpp::cmp::comp((char*) data)
{
}

socketpp::cmp::comp::comp(string data)
  : socketpp::cmp::comp(data.c_str())
{
}

char*
socketpp::cmp::comp::dump()
{
  char* __tmp = this->dump_data;
  this->destroy();
  return __tmp;
}

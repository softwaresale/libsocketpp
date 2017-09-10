
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

#include <iostream>
#include <socketpp/compress/basecmp.h>
#include <socketpp/compress/decomp.h>
#include <cstring>

using namespace std;

socketpp::cmp::decomp::decomp()
  : socketpp::cmp::base_compress()
{
}

socketpp::cmp::decomp::decomp(char* data)
  : socketpp::cmp::base_compress(data)
{
  this->pointer_to_out_data = &data; // derefrence pointer
  this->input_size = (uInt) sizeof(data); // get input size
}

socketpp::cmp::decomp::decomp(const char* data)
  : socketpp::cmp::decomp((char*) data)
{
}

socketpp::cmp::decomp::decomp(string data)
  : socketpp::cmp::decomp(data.c_str())
{
}

void
socketpp::cmp::decomp::inflate_data(char * input)
{
  char* tmp = new char[input_size];

  // this line needs to be fixed...
  stream.avail_in = (uInt) sizeof(input) * 2; // try doubling the size of the input...
  stream.next_in = (Bytef*) input;
  stream.avail_out = input_size;
  stream.next_out = (Bytef*) tmp; // store data in temporary buffer

  // actually do the stuff
  inflateInit(&stream);
  inflate(&stream, Z_NO_FLUSH);
  inflateEnd(&stream);

  // set the tmp data to the derefrenced pointer to the outvalue
  *pointer_to_out_data = tmp; // this should work...
}

int
socketpp::cmp::decomp::getInputSize()
{
  return (int) this->input_size;
}

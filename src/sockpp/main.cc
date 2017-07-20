

/*
  This file is the main entry point of the program `sockpp`.

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
#include <socketpp/tcp/socket.h>
#include <socketpp/tcp/server.h>
#include <getopt.h>
#include <config.h>

using namespace std;
using namespace tcp;

const char* license =
    "
    sockpp  Copyright (C) 2017  Charlie Sale

    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
    This is free software, and you are welcome to redistribute it
    under certain conditions; type `show c' for details.
";

// command line options

int version_flag; // if display versionB
int help_flag;

struct option long_options[] =
{
    {"version", optional_argument, &version_flag, 1},
    {"help", optional_argument, &help_flag, 1},
    {0, 0, 0, 0}
};

/*
 * argv[1] -- address
 * argv[2] -- port
 */

int main(int argc, char** argv)
{
    // default flags to 0
    version_flag = 0;
    help_flags = 0;

    // first, get options
    int index = 0;
    int c = getopt_long(argc, argc, "vh:", long_options, &index);
    if (c == -1){
        cerr << "sockpp:main.cc:56: Could not parse long options" << endl;
        return -1;
    }

    switch(c){
    case 0:
        if (long_options[option_index].flag != 0){
            // testing for now
            cout << "Option: " << long_options[option_index].name << " called" << endl;
        }

        break;

    case 'v':
        version_flag = 1;
        break;

    case 'h':
        help_flag = 1;
        break;

    default:
        cerr << "Something has gone wrong" << endl;
        break;
    }

    if (version_flag){
        cout << PACKAGE_STRING << endl << version_string << endl;

        // just print packaging data
        return 0;
    }

    // begin the actual code

    return 0;
}

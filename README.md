# socketpp
This is a collection of C++ classes for networking with TCP sockets

## Installation
`./configure <prefix>`
`make`
`sudo make install`

## Usage
Compile any files with the `-l socketpp` flags
If you get an error such as:
`./a.out: error while loading shared libraries: libsocketpp.so.0: cannot open shared object file: No such file or directory`

just run `# ldconfig`.
If this command failes to fix your problem,
then add `/usr/local/lib` or where ever you installed the library to
`/etc/ld.so.conf`.

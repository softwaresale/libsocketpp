# Contributing to libsocketpp

Contributions are more than welcome. Here are some notes on how to contribute:

### Building
The project uses autotools (gnu autoconf, gnu automake, gnu libtool, and more)
for configuration and compilation. Make sure that you have them installed.

Once you have cloned into the repository, run the following.
```shell
$ autoreconf -i # (1)
$ mkdir build && cd build # (2)
$ mkdir install # (3)
$ ../configure --prefix=$PWD/install # (4)
$ make # (5)
$ make install # (6)
```
This (1) creates the build files, (2) makes a compilation directory
and moves to it, (3) makes a mock installation directory, (4) configures
the project, (5) compiles the project, and (6) installs it into the
mock installation directory.

Whenever you make changes, just move back to the directory and run
`make` and `make install`.

### Basic Design Structure
Here is a kinda of layout to how this library is designed.

#### Namespaces
Everything is in the namespace `lsock`. This is the project
namespace. Subparts are also in their own namespace. Therefore,
all base classes are in `lsock::base`, all TCP classes in
`lsock::tcp`, and etc.

If you are implementing a new socket type, then make sure to
add a new namespace.

#### Class design structure
All socket types are based off of the class `lsock::base::Socket<_Connector, _AddressType>`.
The classes two template parameters are the connection function (`_Connector`) and the
type of address it uses (`_AddressType`). `_Connector` will be either `lsock::base::Connect`
or `lsock::base::Bind`. They wrap the `connect` and `bind` calls respectivley. `_AddressType`
is the type of address used. This will be something like `struct sockaddr_in` or `struct sockaddr_un`,
although it is not limited to these. It has to be some structure used in `connect` or `bind`.
This class provides functionality for creating a socket, closing it, connecting it with an
address, and preforming basic I/O.

Any socket that streams inherits from `lsock::base::SocketStream`. This uses `lsock::base::SockBuf`
to create a streaming socket based on `std::iostream`.

Any server (i.e socket acceptor) inherits from `lsock::base::Server`. This function provides simple
functionality for accepting a socket stream and returning it to the user. If you implement your
own server, then you should implement an `accept` function, which returns a `std::unique_ptr` of
the corresponding socket type (i.e `lsock::tcp::Server::accept` returns `std::unique_ptr<lsock::tcp::Socket>`).

### Coding Style

This project is written in C++ 17. This means that the project should implement C++ 17 features.

#### Formatting
I personally use Spacemacs for development. For any emacs users out there, I set my C formatting to
`strostroup` mode. Use this setting when writing code.

If you don't use emacs, don't sweat it. What it all really boils down to is *Use 4 space indentation*.

Otherwise, formatting is kinda up to you. There are a few sticky things however.
1. You must use spaces between operators
```cpp
i = i + 5; // good
i=i+4; // bad
```

2. You must have spaces between `if`s and `while`s
```cpp
if (true) // good
if(true) // bad

while (true) // good
while(true) // bad
```

3. All members and methods are lowercase camelCase, and
all member functions are prefixed with `m_`
```cpp
class klass
{
public:
  void func(); // good
  void Bar(); // bad
  void bazFoo(); // good
  void bax_bar(); // bad
  
private:
  int m_val; // good
  char var; // bad
  char mVar; // also bad
};
```

4. All classes are capital CamelCase, and braces go below line
```
class MyClass // good
{};

class myClass { // bad
};
```

5. In implementation file, return type goes on separate line, and
braces goes on next line
```
int
MyClass::bar() // good
{ }

int MyClass::bar() { // bad
}
```

6. Template members are prefixed with `_` and capital letter,
use `typename` and not `class`
```
template <typename _T> // good
class Klass
{};

template <class T> // bad
class BadKlass
{};

template <typename T> // also bad
class BadBadKlass
{};
```

7. Sources files use `.cc` and headers use `.h`
```
src/file.cc // good
src/file.cpp // bad
include/header.h // good
include/header.hpp // bad
include/header // bad
```

Other than that, you can read the code and figure it out. I (think) I'm pretty
consistent.

#### Templates and Class Implementation
Coding with templates can be kinda tricky. One of their big issues is that they
cause linker errors if their templates types are not defined. The two ways to
solve this are to either implement the class in its header, or explicitly
define the templates in implementation files.

As a personal prefrence, I don't like implementing classes in their header files.
It is harder to find issues, and issue come up when the user compiles it. It is
easier to catch issues when everything is compiled. However, there are times to 
use both methods. Here are some guidelines.

If a class uses templates, and the templates are from a predefined option set,
then implement the class in a file and explicitly define its templates. This can
be seen in the class `lsock::base::Socket`. The connector function can only be
either `lsock::base::Bind` or `lsock::base::Connect`, and the address can only
be either `struct sockaddr_in` or `struct sockaddr_un` (for now). So, the class
is implemented in a source file, and the templates are explicity set. See
`src/basesocket.cc` for example.

If a class is a child member of a template class that only sets it's template, then
define the class in the header. See `include/tcp/socket.h` for example.

If a template class is left ambiguous, then define it in the header file.

### Contributing your ideas
If you want to contribute to this project, fork the repository
and look for something to do. Check the issues and the `TODO` file for
something. I (try) keep the TODO file up to date.

Once you have decided on something, file an issue if you are requesting a new feature
or respond to an existing issue if you are fixing it to notify that you are working on
it. The issue will be assigned to the person that says s/he is working on it. 

Make sure that all development happens on a separate branch. Name the branch after the
issue that you are fixing (issue-##) or the name of your feature (feat-...). Also,
make sure that it compiles properly. Compile before commiting. Once whatever you are doing
compiles and works properly, then file a pull request. In it, mention the issue that you
are working on and talk a little bit about how you solved the problem. It will be reviewd,
and hopefully merged into the master branch.

If you contribute, add your name and email to the AUTHORS file for recognition.

If you need help with whatever you are doing, feel free to ask for help in whatever issue
you are working on. I will make sure to help you out. Don't be shy, and no question is a
stupid question.

I wish you happy coding.

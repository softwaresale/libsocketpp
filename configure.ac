#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libsocketpp], [1.0], [softwaresale01@gmail.com])
AC_CONFIG_SRCDIR([src/basesocket.cc])
AC_CONFIG_HEADERS([include/config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([gnu -Wall -Werror])

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AM_PROG_AR
LT_INIT

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h netdb.h netinet/in.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_INT32_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_CHECK_FUNCS([memmove memset socket])
# PKG_CHECK_MODULES([DEPS], [sigc++-2.0])

AC_CONFIG_FILES([Makefile
                 doc/Makefile
                 include/Makefile
                 include/base/Makefile
                 include/inet/Makefile
                 include/tcp/Makefile
                 include/unix/Makefile
                 src/Makefile
		 tests/Makefile])
AC_OUTPUT

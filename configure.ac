AC_INIT([libsocketpp], [0.2], [chucks.8090@gmail.com])
AM_INIT_AUTOMAKE([gnu -Wall -Werror])

AM_PROG_AR

AM_MAINTAINER_MODE

# AC_SUBST([CONFIG_STATUS_DEPENDENCIES], ['$(top_srcdir)/version.sh'])

LT_INIT

AC_PROG_CXX([g++])

AC_CONFIG_HEADERS([include/socketpp/tcp/config.h])

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	include/Makefile
	include/socketpp/Makefile
	include/socketpp/tcp/Makefile
	doc/Makefile
])

AC_OUTPUT

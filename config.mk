# version
VERSION = 0.2.0

# Customize below to fit your system

# paths
PREFIX = /usr
MANPREFIX = ${PREFIX}/share/man

# includes and libs
INCS =
LIBS = -lhpd

# flags
CPPFLAGS =  -DVERSION=\"${VERSION}\"
TESTCFLAGS   = -g -std=c99 -pedantic -Wall -O0 ${INCS} ${CPPFLAGS}
CFLAGS   = -pedantic -Wall -Wno-deprecated-declarations -Os ${INCS} ${CPPFLAGS}
LDFLAGS  = ${LIBS}


# compiler and linker
CC = cc

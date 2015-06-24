#  Make the Xinu version of the C run-time support library

LIB=		libxc.a
LIBDIR=		../lib
AR=		m68k-none-elf-ar
CC=		m68k-none-elf-gcc -mc68000 -mstrict-align
CFLAGS=		-O -c -I../include -ansi -pedantic -std=c11 -Wall -Werror -nostdlib -nostartfiles -ffreestanding
RANLIB=		m68k-none-elf-ranlib

OFILES=		abs.o atoi.o atol.o \
		ctype_.o \
		doprnt.o doscan.o \
		fgets.o fprintf.o fputs.o \
		memchr.o memcmp.o memcpy.o memmove.o memset.o \
		printf.o puts.o \
		qsort.o \
		rand.o \
		scanf.o sprintf.o \
		strcat.o strcmp.o strchr.o strcpy.o strlcat.o strlcpy.o \
		strlen.o strncat.o strncmp.o strncpy.o strrchr.o \
		swab.o

all:		$(LIB)

install:	all
		install -c -m 644 $(LIB) $(LIBDIR)/libxc.a

clean:
		rm -f *.o $(LIB)

libxc.a:	$(OFILES)
		rm -f $(LIB)
		$(AR) cr $(LIB) $(OFILES)
		$(RANLIB) $(LIB)

.c.o:
		$(CC) $(CFLAGS) $<

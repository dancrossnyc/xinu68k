#  Make the Xinu version of the C run-time support library

LIBDIR=		../lib
AR=		m68k-none-elf-ar
CC=		m68k-none-elf-gcc -mc68000 -mstrict-align
CFLAGS=		-O -c -I../include -ansi -pedantic -std=c11 -Wall -Werror -nostdlib -nostartfiles -ffreestanding
RANLIB=		m68k-none-elf-ranlib

OFILES=		abs.o atoi.o atol.o				\
		ctype_.o					\
		doprnt.o doscan.o				\
		fgets.o fprintf.o fputs.o			\
		index.o						\
		memchr.o memcmp.o memcpy.o memmove.o memset.o	\
		printf.o puts.o					\
		qsort.o						\
		rand.o rindex.o					\
		scanf.o sprintf.o				\
		strcat.o strcmp.o strcpy.o strlcat.o strlcpy.o	\
		strlen.o strncat.o strncmp.o strncpy.o swab.o

all:		libxc.a

install:	all
		cp libxc.a $(LIBDIR)/libxc.a
		$(RANLIB) $(LIBDIR)/libxc.a

clean:
		rm -f *.o core a.out libxc.a

libxc.a:	$(OFILES)
		rm -f libxc.a
		$(AR) cr libxc.a $(OFILES)
		$(RANLIB) libxc.a

.c.o:
		$(CC) $(CFLAGS) $<

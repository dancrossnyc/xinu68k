#
#  Make the Xinu version of the C run-time support library
#

DIR	=	/Users/cross/unix/project/xinu68k
LIB	=	$(DIR)/lib
AR	=	m68k-none-elf-ar
AS	=	m68k-none-elf-as
AFLAGS	=	-u $(DIR)/include/sys.s
CC	=	m68k-none-elf-gcc
CFLAGS	=	-O -c -I../../sys/h -ansi -pedantic -std=c11 -Wall -Werror -nostdlib -nostartfiles -ffreestanding
RANLIB	=	m68k-none-elf-ranlib

.s.o:
		$(AS) -o $@ $(AFLAGS) $<

.c.o:
		$(CC) $(CFLAGS) $<

SFILES	=	aldiv.s						\
		almul.s						\
		alrem.s						\
		cerror.s					\
		csv.s						\
		ldiv.s						\
		lmul.s						\
		lrem.s

CFILES	=	abs.c atoi.c atol.c				\
		ctype_.c					\
		doprnt.c doscan.c				\
		fgets.c fprintf.c fputs.c			\
		index.c						\
		printf.c puts.c					\
		qsort.c						\
		rand.c rindex.c					\
		scanf.c sprintf.c				\
		strcat.c strcmp.c strcpy.c strlen.c		\
		strncat.c strncmp.c strncpy.c swab.c

#aldiv.o almul.o alrem.o cerror.o csv.o ldiv.o lmul.o lrem.o

OFILES	=	abs.o						\
		atoi.o atol.o					\
		ctype_.o					\
		doprnt.o doscan.o				\
		fgets.o fprintf.o fputs.o			\
		index.o						\
		printf.o puts.o					\
		qsort.o						\
		rand.o rindex.o					\
		scanf.o sprintf.o				\
		strcat.o strcmp.o strcpy.o strlen.o		\
		strncat.o strncmp.o strncpy.o swab.o


all:		libxc.a

install:	all
		cp libxc.a $(LIB)/libxc.a
		$(RANLIB) $(LIB)/libxc.a

clean:
		rm -rf *.o core a.out libxc.a

libxc.a:	$(OFILES)
		rm -rf libxc.a
		$(AR) cr libxc.a $(OFILES)
		$(RANLIB) libxc.a

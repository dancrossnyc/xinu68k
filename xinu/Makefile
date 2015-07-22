#
#  Makefile for the book version of Xinu
#

DIR=		/Users/cross/unix/project/xinu68k
BINDIR=		$(DIR)/bin
INCDIR=		$(DIR)/include
CONFIG=		./config
CC=		m68k-none-elf-gcc -mc68000 -mstrict-align -fomit-frame-pointer
CFLAGS=		-O -c -I../include -ansi -pedantic -std=c11 -Wall -Werror -nostdlib -nostartfiles -ffreestanding
AS=		m68k-none-elf-as
LD=		m68k-none-elf-ld
AR=		m68k-none-elf-ar
RANLIB=		m68k-none-elf-ranlib
LORDER=		m68k-none-elf-lorder
OBJCOPY=	m68k-none-elf-objcopy
LIB=		$(DIR)/lib

OBJS=		access.o adump.o arp_in.o arpfind.o arpinit.o \
		bpdump.o \
		chprio.o ckmode.o cksum.o clkinit.o \
		clkint.o close.o control.o create.o \
		ctxsw.o \
		devdump.o dfalloc.o dfdsearch.o dgalloc.o \
		dgclose.o dgcntl.o dgdump.o dginit.o \
		dgmcntl.o dgmopen.o dgparse.o dgread.o \
		dgwrite.o dot2ip.o dscntl.o dsinit.o \
		dsinter.o dskbcpy.o dskenq.o dskqopt.o \
		dskstart.o dsksync.o dsopen.o dsread.o \
		dsseek.o dswrite.o dudir.o dumkfs.o \
		etherinit.o etherinter.o etherread.o etherstart.o \
		etherrstart.o etherwrite.o etherwstart.o \
		freebuf.o freemem.o \
		getaddr.o getbuf.o getc.o getitem.o \
		getmem.o getname.o getnet.o getpath.o \
		getpid.o getprio.o getstk.o gettime.o \
		getutime.o \
		ibclear.o ibfree.o ibget.o iblfree.o \
		ibnew.o ibput.o icmp_in.o init.o \
		insert.o insertd.o intr.o ioerr.o \
		ioinit.o ioint.o ionull.o ip2name.o \
		ip_in.o	ipsend.o \
		kill.o kprintf.o \
		lfclose.o lfgetc.o lfinit.o lfputc.o \
		lfread.o lfsdfree.o lfseek.o lfsetup.o \
		lfsflush.o lfsnewd.o lfwrite.o \
		mark.o mdump.o mkarp.o mkpool.o mount.o \
		nameinit.o namemap.o nameopen.o namereplace.o \
		ndump.o netdump.o netin.o netinit.o \
		netnum.o netout.o newqueue.o \
		nqalloc.o \
		open.o \
		panic.o pause.o pcount.o pcreate.o \
		pdelete.o pinit.o poolinit.o prdump.o \
		preceive.o preset.o psend.o ptclear.o \
		putc.o \
		qdump.o queue.o \
		rarp_in.o read.o ready.o receive.o \
		recvclr.o recvtim.o remove.o rename.o \
		resched.o resume.o rfalloc.o rfclose.o \
		rfcntl.o rfdump.o rfgetc.o rfinit.o \
		rfio.o rfmkpac.o rfopen.o rfputc.o \
		rfread.o rfseek.o rfsend.o rfwrite.o \
		route.o rwho.o rwhod.o rwhoind.o \
		scount.o screate.o sdelete.o seek.o \
		send.o sendf.o setclkr.o setdev.o \
		setnok.o sh.o signal.o signaln.o \
		sizmem.o sleep.o sleep10.o sndrarp.o \
		sreset.o ssclock.o suspend.o \
		tdump.o test.o ttycntl.o ttygetc.o \
		ttyiin.o ttyinit.o ttyoin.o ttyopen.o \
		ttyputc.o ttyread.o ttywrite.o \
		udpecho.o udpnxtp.o udpsend.o unmount.o \
		unsleep.o userret.o \
		wait.o wakeup.o write.o \
		xdone.o

XOBJS=		startup.o initialize.o conf.o

all:		libx.a xinu.o

install:	libx.a xinu.o
		cp libx.a $(LIB)/libx.a
		$(RANLIB) $(LIB)/libx.a
		cp xinu.o $(LIB)

clean:
		/bin/rm -f *.o ,* .,* ../include/,* ../include/.,*
		/bin/rm -f libx.a a.out conf.c ../include/conf.h core make.out
		(cd shell && make clean)

sh.o:
		cd shell; make install

libx.a:		$(OBJS)
		/bin/rm -f libx.a
		$(AR) cr libx.a	$(OBJS)
		$(RANLIB) libx.a

xinu.o:		$(XOBJS)
		$(LD) -r $(XOBJS) -o xinu.o

a.out:		libx.a xinu.o test.o
		$(LD) -S -e start -Ttext=0x00001000 -Tdata=0x00080000 xinu.o test.o libx.a libx.a ../lib/libxc.a -L/opt/gnu/lib/gcc/m68k-none-elf/5.2.0/m68000 -lgcc

a.h68:		a.out
		$(OBJCOPY) -O srec a.out a.h68

../include/conf.h:	Configuration
		$(CONFIG)

conf.c:		Configuration
		$(CONFIG)

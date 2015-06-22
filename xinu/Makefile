#
#  Makefile for the book version of Xinu
#

.SUFFIXES:.o .c .s
DIR	=	/Users/cross/unix/project/xinu68k
BINDIR	=	$(DIR)/bin
INCDIR	=	$(DIR)/include
CONFIG	=	./config
CC	=	m68k-none-elf-gcc -mc68000 -mstrict-align
CFLAGS	=	-O -c -I../include -ansi -pedantic -std=c11 -Wall -Werror -nostdlib -nostartfiles -ffreestanding
AFLAGS	=	-u $(INCDIR)/sys.s
AS	=	m68k-none-elf-as
LD	=	m68k-none-elf-ld
AR	=	m68k-none-elf-ar
RANLIB	=	m68k-none-elf-ranlib
LORDER	=	m68k-none-elf-lorder
OBJCOPY	=	m68k-none-elf-objcopy
LIB	=	$(DIR)/lib
DOWNLOAD=	$(BINDIR)/download
SIZE11	=	m68k-none-elf-size
ODT	=	$(BINDIR)/odt
.c.o:
		$(CC) $(CFLAGS)	$<
.s.o:
		$(CC) $(CFLAGS)	$<

CFILES=		access.c adump.c arp_in.c arpfind.c	\
		arpinit.c				\
		bpdump.c				\
		chprio.c ckmode.c cksum.c clkinit.c	\
		close.c conf.c control.c create.c	\
		devdump.c dfalloc.c dfdsrch.c dgalloc.c	\
		dgclose.c dgcntl.c dgdump.c dginit.c	\
		dgmcntl.c dgmopen.c dgparse.c dgread.c	\
		dgwrite.c dot2ip.c dscntl.c dsinit.c	\
		dsinter.c dskbcpy.c dskenq.c dskqopt.c	\
		dskstrt.c dsksync.c dsopen.c dsread.c	\
		dsseek.c dswrite.c dudir.c dumkfs.c	\
		ethinit.c ethinter.c ethread.c ethstrt.c\
		ethrstrt.c ethwrite.c ethwstrt.c	\
		freebuf.c freemem.c			\
		getaddr.c getbuf.c getc.c getitem.c	\
		getmem.c getname.c getnet.c getpath.c	\
		getpid.c getprio.c getstk.c gettime.c	\
		getutim.c				\
		ibclear.c ibfree.c ibget.c iblfree.c	\
		ibnew.c ibput.c icmp_in.c init.c	\
		initialize.c insert.c insertd.c ioerr.c	\
		ioinit.c ionull.c ip2name.c ip_in.c	\
		ipsend.c				\
		kill.c kprintf.c			\
		lfclose.c lfgetc.c lfinit.c lfputc.c	\
		lfread.c lfsdfree.c lfseek.c lfsetup.c	\
		lfsflush.c lfsnewd.c lfwrite.c		\
		mark.c mdump.c mkarp.c mkpool.c mount.c	\
		naminit.c namemap.c namopen.c namrepl.c	\
		ndump.c netdump.c netin.c netinit.c	\
		netnum.c netout.c newqueue.c nqalloc.c	\
		open.c					\
		pcount.c pcreate.c pdelete.c pinit.c	\
		poolinit.c prdump.c preceive.c preset.c	\
		psend.c ptclear.c putc.c		\
		qdump.c queue.c				\
		rarp_in.c read.c ready.c receive.c	\
		recvclr.c recvtim.c remove.c rename.c	\
		resched.c resume.c rfalloc.c rfclose.c	\
		rfcntl.c rfdump.c rfgetc.c rfinit.c	\
		rfio.c rfmkpac.c rfopen.c rfputc.c	\
		rfread.c rfseek.c rfsend.c rfwrite.c	\
		route.c rwho.c rwhod.c rwhoind.c	\
		scount.c screate.c sdelete.c seek.c	\
		send.c sendf.c setdev.c setnok.c	\
		signal.c signaln.c sleep.c sleep10.c	\
		sndrarp.c sreset.c ssclock.c suspend.c	\
		tdump.c test.c ttycntl.c ttygetc.c	\
		ttyiin.c ttyinit.c ttyoin.c ttyopen.c	\
		ttyputc.c ttyread.c ttywrite.c		\
		udpecho.c udpnxtp.c udpsend.c unmount.c	\
		unsleep.c userret.c			\
		wait.c wakeup.c write.c			\
		xdone.c

SFILES=		clkint.s ctxsw.s			\
		intr.s ioint.s				\
		panic.s pause.s				\
		setclkr.s sizmem.s startup.s

OFILES=		access.o adump.o arp_in.o arpfind.o	\
		arpinit.o				\
		bpdump.o				\
		chprio.o ckmode.o cksum.o clkinit.o	\
		clkint.o close.o control.o create.o	\
		ctxsw.o					\
		devdump.o dfalloc.o dfdsrch.o dgalloc.o	\
		dgclose.o dgcntl.o dgdump.o dginit.o	\
		dgmcntl.o dgmopen.o dgparse.o dgread.o	\
		dgwrite.o dot2ip.o dscntl.o dsinit.o	\
		dsinter.o dskbcpy.o dskenq.o dskqopt.o	\
		dskstrt.o dsksync.o dsopen.o dsread.o	\
		dsseek.o dswrite.o dudir.o dumkfs.o	\
		ethinit.o ethinter.o ethread.o ethstrt.o\
		ethrstrt.o ethwrite.o ethwstrt.o	\
		freebuf.o freemem.o			\
		getaddr.o getbuf.o getc.o getitem.o	\
		getmem.o getname.o getnet.o getpath.o	\
		getpid.o getprio.o getstk.o gettime.o	\
		getutim.o				\
		ibclear.o ibfree.o ibget.o iblfree.o	\
		ibnew.o ibput.o icmp_in.o init.o	\
		insert.o insertd.o intr.o ioerr.o	\
		ioinit.o ioint.o ionull.o ip2name.o	\
		ip_in.o	ipsend.o			\
		kill.o kprintf.o			\
		lfclose.o lfgetc.o lfinit.o lfputc.o	\
		lfread.o lfsdfree.o lfseek.o lfsetup.o	\
		lfsflush.o lfsnewd.o lfwrite.o		\
		mark.o mdump.o mkarp.o mkpool.o mount.o	\
		naminit.o namemap.o namopen.o namrepl.o	\
		ndump.o netdump.o netin.o netinit.o	\
		netnum.o netout.o newqueue.o		\
		nqalloc.o				\
		open.o					\
		panic.o pause.o pcount.o pcreate.o	\
		pdelete.o pinit.o poolinit.o prdump.o 	\
		preceive.o preset.o psend.o ptclear.o	\
		putc.o					\
		qdump.o queue.o				\
		rarp_in.o read.o ready.o receive.o	\
		recvclr.o recvtim.o remove.o rename.o	\
		resched.o resume.o rfalloc.o rfclose.o	\
		rfcntl.o rfdump.o rfgetc.o rfinit.o	\
		rfio.o rfmkpac.o rfopen.o rfputc.o	\
		rfread.o rfseek.o rfsend.o rfwrite.o	\
		route.o rwho.o rwhod.o rwhoind.o	\
		scount.o screate.o sdelete.o seek.o	\
		send.o sendf.o setclkr.o setdev.o	\
		setnok.o sh.o signal.o signaln.o	\
		sizmem.o sleep.o sleep10.o sndrarp.o	\
		sreset.o ssclock.o suspend.o		\
		tdump.o test.o ttycntl.o ttygetc.o	\
		ttyiin.o ttyinit.o ttyoin.o ttyopen.o	\
		ttyputc.o ttyread.o ttywrite.o		\
		udpecho.o udpnxtp.o udpsend.o unmount.o	\
		unsleep.o userret.o			\
		wait.o wakeup.o write.o			\
		xdone.o

XOFILES=	startup.o initialize.o conf.o

HFILES=		../include/a.out.h ../include/arp.h ../include/bufpool.h	\
		../include/cmd.h ../include/conf.h	\
		../include/ctype.h ../include/date.h ../include/deqna.h	\
		../include/dgram.h ../include/dir.h ../include/disk.h	\
		../include/domain.h ../include/dtc.h ../include/ether.h	\
		../include/file.h ../include/fserver.h ../include/hosts.h	\
		../include/iblock.h ../include/icmp.h ../include/io.h	\
		../include/ip.h ../include/kernel.h ../include/lfile.h	\
		../include/mark.h ../include/mem.h ../include/name.h	\
		../include/net.h ../include/network.h ../include/ports.h	\
		../include/proc.h ../include/q.h ../include/rfile.h	\
		../include/rwho.h ../include/sem.h ../include/shell.h	\
		../include/sleep.h ../include/slu.h ../include/tty.h	\
		../include/udp.h ../include/unix-rwho.h ../include/xebec.h

all:		libx.a xinu.o

install:	libx.a xinu.o
		cp libx.a $(LIB)/libx.a
		$(RANLIB) $(LIB)/libx.a
		cp xinu.o $(LIB)

clean:
		-/bin/rm -f *.o ,* .,* ../include/,* ../include/.,*
		-/bin/rm -f libx.a a.out conf.c ../include/conf.h core make.out
		-(cd shell && make clean)

everything:	a.out xref checkup sizes lint

down:		a.out
		$(DOWNLOAD) -s

d:		a.out
		$(DOWNLOAD) -s
		$(ODT)

checkup:
		./Checkup

sizes:		,sizes ,ssizes

,sizes:		$(OFILES) $(XOFILES) a.out
		$(SIZE11) *.o a.out > ,sizes

,ssizes:	$(CFILES) $(SFILES) $(HFILES)
		./Dosizes

sh.o:
		cd shell; make install

libx.a:		$(OFILES)
		/bin/rm -f  libx.a
		$(AR) cr libx.a	$(OFILES)
		$(RANLIB) libx.a

xinu.o:		$(XOFILES)
		$(LD) -r $(XOFILES) -o xinu.o

a.out:		libx.a xinu.o test.o
		$(LD) -S -e start -Ttext=0x00001000 -Tdata=0x00080000 xinu.o test.o libx.a libx.a ../lib/libxc.a -L/opt/gnu/lib/gcc/m68k-none-elf/4.9.2/m68000 -lgcc

a.h68:		a.out
		$(OBJCOPY) -O srec a.out a.h68

tags:		,tags

,tags:		$(CFILES) $(HFILES)
		ctags $(CFILES)	$(HFILES)
		/bin/mv tags ,tags

xref:		,xref

,xref:		,tags
		./Doxref

../include/conf.h:	Configuration
		$(CONFIG)

conf.c:		Configuration
		$(CONFIG)

depend:
		grep '^#include' *.c ../include/*.h			\
		| sed	-e 's/</"..\/h\//;s/>/"/'		\
			-e 's/:[^"]*"\([^"]*\)".*/: \1/'	\
		| sed	's/\.c/.o/' >makedep
		echo '/^# DO NOT DELETE	THIS LINE/+2,$$d' >eddep
		echo '$$r makedep' >>eddep
		echo 'w' >>eddep
		cp Makefile .,oldmake
		cp Makefile ,Makefile
		ed - ,Makefile < eddep
		/bin/rm eddep makedep
		echo '#	DEPENDENCIES MUST END AT END OF	FILE' >>,Makefile
		echo '#	IF YOU PUT STUFF HERE IT WILL GO AWAY'>>,Makefile
		echo '#	see make depend	above'>>,Makefile
		/bin/mv ,Makefile Makefile

# DO NOT DELETE	THIS LINE
# DEPENDENCIES MUST END	AT END OF FILE
access.o: ../include/conf.h
access.o: ../include/kernel.h
access.o: ../include/file.h
access.o: ../include/name.h
adump.o: ../include/conf.h
adump.o: ../include/kernel.h
adump.o: ../include/proc.h
adump.o: ../include/network.h
arp_in.o: ../include/conf.h
arp_in.o: ../include/kernel.h
arp_in.o: ../include/proc.h
arp_in.o: ../include/network.h
arpfind.o: ../include/conf.h
arpfind.o: ../include/kernel.h
arpfind.o: ../include/proc.h
arpfind.o: ../include/network.h
arpinit.o: ../include/conf.h
arpinit.o: ../include/kernel.h
arpinit.o: ../include/proc.h
arpinit.o: ../include/network.h
bpdump.o: ../include/conf.h
bpdump.o: ../include/kernel.h
bpdump.o: ../include/mark.h
bpdump.o: ../include/bufpool.h
chprio.o: ../include/conf.h
chprio.o: ../include/kernel.h
chprio.o: ../include/proc.h
ckmode.o: ../include/conf.h
ckmode.o: ../include/kernel.h
ckmode.o: ../include/file.h
clkinit.o: ../include/conf.h
clkinit.o: ../include/kernel.h
clkinit.o: ../include/sleep.h
close.o: ../include/conf.h
close.o: ../include/kernel.h
close.o: ../include/io.h
conf.o: ../include/conf.h
control.o: ../include/conf.h
control.o: ../include/kernel.h
control.o: ../include/io.h
create.o: ../include/conf.h
create.o: ../include/kernel.h
create.o: ../include/proc.h
create.o: ../include/mem.h
create.o: ../include/io.h
devdump.o: ../include/conf.h
devdump.o: ../include/kernel.h
dfalloc.o: ../include/conf.h
dfalloc.o: ../include/kernel.h
dfalloc.o: ../include/disk.h
dfalloc.o: ../include/lfile.h
dfdsrch.o: ../include/conf.h
dfdsrch.o: ../include/kernel.h
dfdsrch.o: ../include/disk.h
dfdsrch.o: ../include/lfile.h
dfdsrch.o: ../include/dir.h
dgalloc.o: ../include/conf.h
dgalloc.o: ../include/kernel.h
dgalloc.o: ../include/network.h
dgclose.o: ../include/conf.h
dgclose.o: ../include/kernel.h
dgclose.o: ../include/proc.h
dgclose.o: ../include/network.h
dgcntl.o: ../include/conf.h
dgcntl.o: ../include/kernel.h
dgcntl.o: ../include/network.h
dgdump.o: ../include/conf.h
dgdump.o: ../include/kernel.h
dgdump.o: ../include/network.h
dginit.o: ../include/conf.h
dginit.o: ../include/kernel.h
dginit.o: ../include/network.h
dgmcntl.o: ../include/conf.h
dgmcntl.o: ../include/kernel.h
dgmcntl.o: ../include/network.h
dgmopen.o: ../include/conf.h
dgmopen.o: ../include/kernel.h
dgmopen.o: ../include/network.h
dgparse.o: ../include/conf.h
dgparse.o: ../include/kernel.h
dgparse.o: ../include/network.h
dgparse.o: ../include/ctype.h
dgread.o: ../include/conf.h
dgread.o: ../include/kernel.h
dgread.o: ../include/proc.h
dgread.o: ../include/network.h
dgwrite.o: ../include/conf.h
dgwrite.o: ../include/kernel.h
dgwrite.o: ../include/network.h
dot2ip.o: ../include/conf.h
dot2ip.o: ../include/kernel.h
dot2ip.o: ../include/network.h
dscntl.o: ../include/conf.h
dscntl.o: ../include/kernel.h
dscntl.o: ../include/proc.h
dscntl.o: ../include/disk.h
dsinit.o: ../include/conf.h
dsinit.o: ../include/kernel.h
dsinit.o: ../include/disk.h
dsinter.o: ../include/conf.h
dsinter.o: ../include/kernel.h
dsinter.o: ../include/disk.h
dskbcpy.o: ../include/conf.h
dskbcpy.o: ../include/kernel.h
dskbcpy.o: ../include/disk.h
dskenq.o: ../include/conf.h
dskenq.o: ../include/kernel.h
dskenq.o: ../include/disk.h
dskqopt.o: ../include/conf.h
dskqopt.o: ../include/kernel.h
dskqopt.o: ../include/disk.h
dskstrt.o: ../include/conf.h
dskstrt.o: ../include/kernel.h
dskstrt.o: ../include/disk.h
dsksync.o: ../include/conf.h
dsksync.o: ../include/kernel.h
dsksync.o: ../include/proc.h
dsksync.o: ../include/disk.h
dsopen.o: ../include/conf.h
dsopen.o: ../include/kernel.h
dsopen.o: ../include/disk.h
dsopen.o: ../include/lfile.h
dsopen.o: ../include/dir.h
dsread.o: ../include/conf.h
dsread.o: ../include/kernel.h
dsread.o: ../include/proc.h
dsread.o: ../include/disk.h
dsseek.o: ../include/conf.h
dsseek.o: ../include/kernel.h
dsseek.o: ../include/proc.h
dsseek.o: ../include/disk.h
dswrite.o: ../include/conf.h
dswrite.o: ../include/kernel.h
dswrite.o: ../include/proc.h
dswrite.o: ../include/disk.h
dudir.o: ../include/conf.h
dudir.o: ../include/kernel.h
dudir.o: ../include/io.h
dudir.o: ../include/disk.h
dudir.o: ../include/lfile.h
dudir.o: ../include/dir.h
dumkfs.o: ../include/conf.h
dumkfs.o: ../include/kernel.h
dumkfs.o: ../include/disk.h
dumkfs.o: ../include/lfile.h
dumkfs.o: ../include/dir.h
ethinit.o: ../include/conf.h
ethinit.o: ../include/kernel.h
ethinit.o: ../include/network.h
ethinter.o: ../include/conf.h
ethinter.o: ../include/kernel.h
ethinter.o: ../include/proc.h
ethinter.o: ../include/network.h
ethread.o: ../include/conf.h
ethread.o: ../include/kernel.h
ethread.o: ../include/proc.h
ethread.o: ../include/network.h
ethrstrt.o: ../include/conf.h
ethrstrt.o: ../include/kernel.h
ethrstrt.o: ../include/network.h
ethstrt.o: ../include/conf.h
ethstrt.o: ../include/kernel.h
ethstrt.o: ../include/network.h
ethwrite.o: ../include/conf.h
ethwrite.o: ../include/kernel.h
ethwrite.o: ../include/proc.h
ethwrite.o: ../include/network.h
ethwstrt.o: ../include/conf.h
ethwstrt.o: ../include/kernel.h
ethwstrt.o: ../include/proc.h
ethwstrt.o: ../include/network.h
freebuf.o: ../include/conf.h
freebuf.o: ../include/kernel.h
freebuf.o: ../include/mark.h
freebuf.o: ../include/bufpool.h
freemem.o: ../include/conf.h
freemem.o: ../include/kernel.h
freemem.o: ../include/mem.h
getaddr.o: ../include/conf.h
getaddr.o: ../include/kernel.h
getaddr.o: ../include/network.h
getbuf.o: ../include/conf.h
getbuf.o: ../include/kernel.h
getbuf.o: ../include/mark.h
getbuf.o: ../include/bufpool.h
getc.o: ../include/conf.h
getc.o: ../include/kernel.h
getc.o: ../include/io.h
getitem.o: ../include/conf.h
getitem.o: ../include/kernel.h
getitem.o: ../include/q.h
getmem.o: ../include/conf.h
getmem.o: ../include/kernel.h
getmem.o: ../include/mem.h
getname.o: ../include/conf.h
getname.o: ../include/kernel.h
getname.o: ../include/network.h
getnet.o: ../include/conf.h
getnet.o: ../include/kernel.h
getnet.o: ../include/network.h
getpath.o: ../include/conf.h
getpath.o: ../include/kernel.h
getpath.o: ../include/proc.h
getpath.o: ../include/network.h
getpid.o: ../include/conf.h
getpid.o: ../include/kernel.h
getpid.o: ../include/proc.h
getprio.o: ../include/conf.h
getprio.o: ../include/kernel.h
getprio.o: ../include/proc.h
getstk.o: ../include/conf.h
getstk.o: ../include/kernel.h
getstk.o: ../include/mem.h
gettime.o: ../include/conf.h
gettime.o: ../include/kernel.h
gettime.o: ../include/date.h
getutim.o: ../include/conf.h
getutim.o: ../include/kernel.h
getutim.o: ../include/sleep.h
getutim.o: ../include/date.h
getutim.o: ../include/network.h
ibclear.o: ../include/conf.h
ibclear.o: ../include/kernel.h
ibclear.o: ../include/disk.h
ibclear.o: ../include/lfile.h
ibclear.o: ../include/dir.h
ibfree.o: ../include/conf.h
ibfree.o: ../include/kernel.h
ibfree.o: ../include/io.h
ibfree.o: ../include/disk.h
ibfree.o: ../include/lfile.h
ibfree.o: ../include/dir.h
ibget.o: ../include/conf.h
ibget.o: ../include/kernel.h
ibget.o: ../include/disk.h
ibget.o: ../include/lfile.h
ibget.o: ../include/dir.h
iblfree.o: ../include/conf.h
iblfree.o: ../include/kernel.h
iblfree.o: ../include/io.h
iblfree.o: ../include/disk.h
iblfree.o: ../include/lfile.h
iblfree.o: ../include/dir.h
ibnew.o: ../include/conf.h
ibnew.o: ../include/kernel.h
ibnew.o: ../include/io.h
ibnew.o: ../include/disk.h
ibnew.o: ../include/lfile.h
ibnew.o: ../include/dir.h
ibput.o: ../include/conf.h
ibput.o: ../include/kernel.h
ibput.o: ../include/io.h
ibput.o: ../include/disk.h
ibput.o: ../include/lfile.h
ibput.o: ../include/dir.h
icmp_in.o: ../include/conf.h
icmp_in.o: ../include/kernel.h
icmp_in.o: ../include/network.h
init.o: ../include/conf.h
init.o: ../include/kernel.h
init.o: ../include/io.h
initialize.o: ../include/conf.h
initialize.o: ../include/kernel.h
initialize.o: ../include/proc.h
initialize.o: ../include/sem.h
initialize.o: ../include/sleep.h
initialize.o: ../include/mem.h
initialize.o: ../include/tty.h
initialize.o: ../include/q.h
initialize.o: ../include/io.h
initialize.o: ../include/disk.h
initialize.o: ../include/network.h
insert.o: ../include/conf.h
insert.o: ../include/kernel.h
insert.o: ../include/q.h
insertd.o: ../include/conf.h
insertd.o: ../include/kernel.h
insertd.o: ../include/q.h
ioerr.o: ../include/conf.h
ioerr.o: ../include/kernel.h
ioinit.o: ../include/conf.h
ioinit.o: ../include/kernel.h
ioinit.o: ../include/io.h
ionull.o: ../include/conf.h
ionull.o: ../include/kernel.h
ip2name.o: ../include/conf.h
ip2name.o: ../include/kernel.h
ip2name.o: ../include/network.h
ip_in.o: ../include/conf.h
ip_in.o: ../include/kernel.h
ip_in.o: ../include/proc.h
ip_in.o: ../include/network.h
ipsend.o: ../include/conf.h
ipsend.o: ../include/kernel.h
ipsend.o: ../include/network.h
kill.o: ../include/conf.h
kill.o: ../include/kernel.h
kill.o: ../include/proc.h
kill.o: ../include/sem.h
kill.o: ../include/mem.h
kill.o: ../include/io.h
kprintf.o: ../include/conf.h
kprintf.o: ../include/kernel.h
kprintf.o: ../include/io.h
kprintf.o: ../include/slu.h
kprintf.o: ../include/tty.h
lfclose.o: ../include/conf.h
lfclose.o: ../include/kernel.h
lfclose.o: ../include/proc.h
lfclose.o: ../include/disk.h
lfclose.o: ../include/lfile.h
lfclose.o: ../include/dir.h
lfgetc.o: ../include/conf.h
lfgetc.o: ../include/kernel.h
lfgetc.o: ../include/proc.h
lfgetc.o: ../include/disk.h
lfgetc.o: ../include/lfile.h
lfgetc.o: ../include/dir.h
lfinit.o: ../include/conf.h
lfinit.o: ../include/kernel.h
lfinit.o: ../include/disk.h
lfinit.o: ../include/lfile.h
lfputc.o: ../include/conf.h
lfputc.o: ../include/kernel.h
lfputc.o: ../include/proc.h
lfputc.o: ../include/disk.h
lfputc.o: ../include/lfile.h
lfputc.o: ../include/dir.h
lfread.o: ../include/conf.h
lfread.o: ../include/kernel.h
lfread.o: ../include/disk.h
lfread.o: ../include/lfile.h
lfread.o: ../include/dir.h
lfsdfree.o: ../include/conf.h
lfsdfree.o: ../include/kernel.h
lfsdfree.o: ../include/disk.h
lfsdfree.o: ../include/lfile.h
lfsdfree.o: ../include/dir.h
lfseek.o: ../include/conf.h
lfseek.o: ../include/kernel.h
lfseek.o: ../include/disk.h
lfseek.o: ../include/lfile.h
lfseek.o: ../include/dir.h
lfsetup.o: ../include/conf.h
lfsetup.o: ../include/kernel.h
lfsetup.o: ../include/disk.h
lfsetup.o: ../include/lfile.h
lfsetup.o: ../include/dir.h
lfsflush.o: ../include/conf.h
lfsflush.o: ../include/kernel.h
lfsflush.o: ../include/disk.h
lfsflush.o: ../include/lfile.h
lfsflush.o: ../include/dir.h
lfsnewd.o: ../include/conf.h
lfsnewd.o: ../include/kernel.h
lfsnewd.o: ../include/disk.h
lfsnewd.o: ../include/lfile.h
lfsnewd.o: ../include/dir.h
lfwrite.o: ../include/conf.h
lfwrite.o: ../include/kernel.h
mark.o: ../include/conf.h
mark.o: ../include/kernel.h
mark.o: ../include/mark.h
mdump.o: ../include/conf.h
mdump.o: ../include/kernel.h
mdump.o: ../include/proc.h
mdump.o: ../include/mem.h
mkarp.o: ../include/conf.h
mkarp.o: ../include/kernel.h
mkarp.o: ../include/network.h
mkpool.o: ../include/conf.h
mkpool.o: ../include/kernel.h
mkpool.o: ../include/mark.h
mkpool.o: ../include/bufpool.h
mount.o: ../include/conf.h
mount.o: ../include/kernel.h
mount.o: ../include/name.h
naminit.o: ../include/conf.h
naminit.o: ../include/kernel.h
naminit.o: ../include/name.h
namemap.o: ../include/conf.h
namemap.o: ../include/kernel.h
namemap.o: ../include/name.h
namopen.o: ../include/conf.h
namopen.o: ../include/kernel.h
namopen.o: ../include/name.h
namrepl.o: ../include/conf.h
namrepl.o: ../include/kernel.h
namrepl.o: ../include/name.h
ndump.o: ../include/conf.h
ndump.o: ../include/kernel.h
ndump.o: ../include/io.h
ndump.o: ../include/name.h
netdump.o: ../include/conf.h
netdump.o: ../include/kernel.h
netdump.o: ../include/network.h
netin.o: ../include/conf.h
netin.o: ../include/kernel.h
netin.o: ../include/proc.h
netin.o: ../include/network.h
netinit.o: ../include/conf.h
netinit.o: ../include/kernel.h
netinit.o: ../include/sleep.h
netinit.o: ../include/network.h
netnum.o: ../include/conf.h
netnum.o: ../include/kernel.h
netnum.o: ../include/network.h
netout.o: ../include/conf.h
netout.o: ../include/kernel.h
netout.o: ../include/network.h
newqueue.o: ../include/conf.h
newqueue.o: ../include/kernel.h
newqueue.o: ../include/q.h
nqalloc.o: ../include/conf.h
nqalloc.o: ../include/kernel.h
nqalloc.o: ../include/proc.h
nqalloc.o: ../include/network.h
open.o: ../include/conf.h
open.o: ../include/kernel.h
open.o: ../include/io.h
pcount.o: ../include/conf.h
pcount.o: ../include/kernel.h
pcount.o: ../include/mark.h
pcount.o: ../include/ports.h
pcreate.o: ../include/conf.h
pcreate.o: ../include/kernel.h
pcreate.o: ../include/mark.h
pcreate.o: ../include/ports.h
pdelete.o: ../include/conf.h
pdelete.o: ../include/kernel.h
pdelete.o: ../include/mark.h
pdelete.o: ../include/ports.h
pinit.o: ../include/conf.h
pinit.o: ../include/kernel.h
pinit.o: ../include/mark.h
pinit.o: ../include/ports.h
poolinit.o: ../include/conf.h
poolinit.o: ../include/kernel.h
poolinit.o: ../include/mark.h
poolinit.o: ../include/bufpool.h
prdump.o: ../include/conf.h
prdump.o: ../include/kernel.h
prdump.o: ../include/proc.h
prdump.o: ../include/q.h
preceive.o: ../include/conf.h
preceive.o: ../include/kernel.h
preceive.o: ../include/mark.h
preceive.o: ../include/ports.h
preset.o: ../include/conf.h
preset.o: ../include/kernel.h
preset.o: ../include/mark.h
preset.o: ../include/ports.h
psend.o: ../include/conf.h
psend.o: ../include/kernel.h
psend.o: ../include/mark.h
psend.o: ../include/ports.h
ptclear.o: ../include/conf.h
ptclear.o: ../include/kernel.h
ptclear.o: ../include/mark.h
ptclear.o: ../include/ports.h
putc.o: ../include/conf.h
putc.o: ../include/kernel.h
putc.o: ../include/io.h
qdump.o: ../include/conf.h
qdump.o: ../include/kernel.h
qdump.o: ../include/proc.h
qdump.o: ../include/q.h
queue.o: ../include/conf.h
queue.o: ../include/kernel.h
queue.o: ../include/q.h
rarp_in.o: ../include/conf.h
rarp_in.o: ../include/kernel.h
rarp_in.o: ../include/proc.h
rarp_in.o: ../include/network.h
read.o: ../include/conf.h
read.o: ../include/kernel.h
read.o: ../include/io.h
ready.o: ../include/conf.h
ready.o: ../include/kernel.h
ready.o: ../include/proc.h
ready.o: ../include/q.h
receive.o: ../include/conf.h
receive.o: ../include/kernel.h
receive.o: ../include/proc.h
recvclr.o: ../include/conf.h
recvclr.o: ../include/kernel.h
recvclr.o: ../include/proc.h
recvtim.o: ../include/conf.h
recvtim.o: ../include/kernel.h
recvtim.o: ../include/proc.h
recvtim.o: ../include/q.h
recvtim.o: ../include/sleep.h
remove.o: ../include/conf.h
remove.o: ../include/kernel.h
remove.o: ../include/file.h
remove.o: ../include/name.h
rename.o: ../include/conf.h
rename.o: ../include/kernel.h
rename.o: ../include/file.h
rename.o: ../include/name.h
resched.o: ../include/conf.h
resched.o: ../include/kernel.h
resched.o: ../include/proc.h
resched.o: ../include/q.h
resume.o: ../include/conf.h
resume.o: ../include/kernel.h
resume.o: ../include/proc.h
rfalloc.o: ../include/conf.h
rfalloc.o: ../include/kernel.h
rfalloc.o: ../include/fserver.h
rfalloc.o: ../include/rfile.h
rfclose.o: ../include/conf.h
rfclose.o: ../include/kernel.h
rfclose.o: ../include/network.h
rfcntl.o: ../include/conf.h
rfcntl.o: ../include/kernel.h
rfcntl.o: ../include/network.h
rfdump.o: ../include/conf.h
rfdump.o: ../include/kernel.h
rfdump.o: ../include/fserver.h
rfdump.o: ../include/rfile.h
rfgetc.o: ../include/conf.h
rfgetc.o: ../include/kernel.h
rfgetc.o: ../include/network.h
rfinit.o: ../include/conf.h
rfinit.o: ../include/kernel.h
rfinit.o: ../include/fserver.h
rfinit.o: ../include/rfile.h
rfio.o: ../include/conf.h
rfio.o: ../include/kernel.h
rfio.o: ../include/network.h
rfmkpac.o: ../include/conf.h
rfmkpac.o: ../include/kernel.h
rfmkpac.o: ../include/network.h
rfopen.o: ../include/conf.h
rfopen.o: ../include/kernel.h
rfopen.o: ../include/network.h
rfputc.o: ../include/conf.h
rfputc.o: ../include/kernel.h
rfputc.o: ../include/network.h
rfread.o: ../include/conf.h
rfread.o: ../include/kernel.h
rfread.o: ../include/network.h
rfseek.o: ../include/conf.h
rfseek.o: ../include/kernel.h
rfseek.o: ../include/fserver.h
rfseek.o: ../include/rfile.h
rfsend.o: ../include/conf.h
rfsend.o: ../include/kernel.h
rfsend.o: ../include/network.h
rfwrite.o: ../include/conf.h
rfwrite.o: ../include/kernel.h
rfwrite.o: ../include/network.h
route.o: ../include/conf.h
route.o: ../include/kernel.h
route.o: ../include/network.h
rwho.o: ../include/conf.h
rwho.o: ../include/kernel.h
rwho.o: ../include/network.h
rwho.o: ../include/rwho.h
rwhod.o: ../include/conf.h
rwhod.o: ../include/kernel.h
rwhod.o: ../include/network.h
rwhod.o: ../include/rwho.h
rwhod.o: ../include/shell.h
rwhoind.o: ../include/conf.h
rwhoind.o: ../include/kernel.h
rwhoind.o: ../include/network.h
rwhoind.o: ../include/rwho.h
scount.o: ../include/conf.h
scount.o: ../include/kernel.h
scount.o: ../include/sem.h
screate.o: ../include/conf.h
screate.o: ../include/kernel.h
screate.o: ../include/proc.h
screate.o: ../include/q.h
screate.o: ../include/sem.h
sdelete.o: ../include/conf.h
sdelete.o: ../include/kernel.h
sdelete.o: ../include/proc.h
sdelete.o: ../include/q.h
sdelete.o: ../include/sem.h
seek.o: ../include/conf.h
seek.o: ../include/kernel.h
seek.o: ../include/io.h
send.o: ../include/conf.h
send.o: ../include/kernel.h
send.o: ../include/proc.h
sendf.o: ../include/conf.h
sendf.o: ../include/kernel.h
sendf.o: ../include/proc.h
setdev.o: ../include/conf.h
setdev.o: ../include/kernel.h
setdev.o: ../include/proc.h
setnok.o: ../include/conf.h
setnok.o: ../include/kernel.h
setnok.o: ../include/proc.h
signal.o: ../include/conf.h
signal.o: ../include/kernel.h
signal.o: ../include/proc.h
signal.o: ../include/q.h
signal.o: ../include/sem.h
signaln.o: ../include/conf.h
signaln.o: ../include/kernel.h
signaln.o: ../include/proc.h
signaln.o: ../include/q.h
signaln.o: ../include/sem.h
sleep.o: ../include/conf.h
sleep.o: ../include/kernel.h
sleep.o: ../include/proc.h
sleep.o: ../include/q.h
sleep.o: ../include/sleep.h
sleep10.o: ../include/conf.h
sleep10.o: ../include/kernel.h
sleep10.o: ../include/proc.h
sleep10.o: ../include/q.h
sleep10.o: ../include/sleep.h
sndrarp.o: ../include/conf.h
sndrarp.o: ../include/kernel.h
sndrarp.o: ../include/network.h
sreset.o: ../include/conf.h
sreset.o: ../include/kernel.h
sreset.o: ../include/proc.h
sreset.o: ../include/q.h
sreset.o: ../include/sem.h
ssclock.o: ../include/conf.h
ssclock.o: ../include/kernel.h
ssclock.o: ../include/proc.h
ssclock.o: ../include/q.h
ssclock.o: ../include/sleep.h
suspend.o: ../include/conf.h
suspend.o: ../include/kernel.h
suspend.o: ../include/proc.h
tdump.o: ../include/conf.h
tdump.o: ../include/kernel.h
tdump.o: ../include/tty.h
test.o: ../include/conf.h
test.o: ../include/kernel.h
test.o: ../include/network.h
ttycntl.o: ../include/conf.h
ttycntl.o: ../include/kernel.h
ttycntl.o: ../include/tty.h
ttycntl.o: ../include/io.h
ttycntl.o: ../include/slu.h
ttygetc.o: ../include/conf.h
ttygetc.o: ../include/kernel.h
ttygetc.o: ../include/tty.h
ttygetc.o: ../include/io.h
ttyiin.o: ../include/conf.h
ttyiin.o: ../include/kernel.h
ttyiin.o: ../include/tty.h
ttyiin.o: ../include/io.h
ttyiin.o: ../include/slu.h
ttyinit.o: ../include/conf.h
ttyinit.o: ../include/kernel.h
ttyinit.o: ../include/proc.h
ttyinit.o: ../include/tty.h
ttyinit.o: ../include/io.h
ttyinit.o: ../include/slu.h
ttyoin.o: ../include/conf.h
ttyoin.o: ../include/kernel.h
ttyoin.o: ../include/tty.h
ttyoin.o: ../include/io.h
ttyoin.o: ../include/slu.h
ttyopen.o: ../include/conf.h
ttyopen.o: ../include/kernel.h
ttyputc.o: ../include/conf.h
ttyputc.o: ../include/kernel.h
ttyputc.o: ../include/tty.h
ttyputc.o: ../include/io.h
ttyputc.o: ../include/slu.h
ttyread.o: ../include/conf.h
ttyread.o: ../include/kernel.h
ttyread.o: ../include/tty.h
ttyread.o: ../include/io.h
ttywrite.o: ../include/conf.h
ttywrite.o: ../include/kernel.h
ttywrite.o: ../include/tty.h
ttywrite.o: ../include/io.h
ttywrite.o: ../include/slu.h
udpecho.o: ../include/conf.h
udpecho.o: ../include/kernel.h
udpecho.o: ../include/network.h
udpnxtp.o: ../include/conf.h
udpnxtp.o: ../include/kernel.h
udpnxtp.o: ../include/network.h
udpsend.o: ../include/conf.h
udpsend.o: ../include/kernel.h
udpsend.o: ../include/network.h
unmount.o: ../include/conf.h
unmount.o: ../include/kernel.h
unmount.o: ../include/name.h
unsleep.o: ../include/conf.h
unsleep.o: ../include/kernel.h
unsleep.o: ../include/proc.h
unsleep.o: ../include/q.h
unsleep.o: ../include/sleep.h
userret.o: ../include/conf.h
userret.o: ../include/kernel.h
wait.o: ../include/conf.h
wait.o: ../include/kernel.h
wait.o: ../include/proc.h
wait.o: ../include/q.h
wait.o: ../include/sem.h
wakeup.o: ../include/conf.h
wakeup.o: ../include/kernel.h
wakeup.o: ../include/proc.h
wakeup.o: ../include/q.h
wakeup.o: ../include/sleep.h
write.o: ../include/conf.h
write.o: ../include/kernel.h
write.o: ../include/io.h
../include/disk.h: ../include/xebec.h
../include/disk.h: ../include/dtc.h
../include/lfile.h: ../include/iblock.h
../include/lfile.h: ../include/file.h
../include/network.h: ../include/deqna.h
../include/network.h: ../include/ether.h
../include/network.h: ../include/ip.h
../include/network.h: ../include/icmp.h
../include/network.h: ../include/udp.h
../include/network.h: ../include/net.h
../include/network.h: ../include/dgram.h
../include/network.h: ../include/arp.h
../include/network.h: ../include/fserver.h
../include/network.h: ../include/rfile.h
../include/network.h: ../include/domain.h
../include/rfile.h: ../include/file.h
../include/shell.h: ../include/mark.h
#	DEPENDENCIES MUST END AT END OF	FILE
#	IF YOU PUT STUFF HERE IT WILL GO AWAY
#	see make depend	above

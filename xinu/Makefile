#
#  Makefile for the book version of Xinu
#

DIR=		/Users/cross/unix/project/xinu68k
BINDIR=		$(DIR)/bin
INCDIR=		$(DIR)/include
CONFIG=		./config
CC=		m68k-none-elf-gcc -mc68000 -mstrict-align
CFLAGS=		-O -c -I../include -I. -ansi -pedantic -std=c11 -Wall -Werror -nostdlib -nostartfiles -ffreestanding
AS=		m68k-none-elf-as
LD=		m68k-none-elf-ld
AR=		m68k-none-elf-ar
RANLIB=		m68k-none-elf-ranlib
LORDER=		m68k-none-elf-lorder
OBJCOPY=	m68k-none-elf-objcopy
LIB=		$(DIR)/lib

OBJS=		startup.o initialize.o conf.o \
		access.o adump.o arp_in.o arpfind.o arpinit.o \
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
		recvclr.o recvtime.o remove.o rename.o \
		resched.o resume.o rfalloc.o rfclose.o \
		rfcntl.o rfdump.o rfgetc.o rfinit.o \
		rfio.o rfmkpac.o rfopen.o rfputc.o \
		rfread.o rfseek.o rfsend.o rfwrite.o \
		route.o rwho.o rwhod.o rwhoind.o \
		scount.o screate.o sdelete.o seek.o \
		send.o sendf.o setclkr.o setdev.o \
		setnok.o signal.o signaln.o \
		sizmem.o sleep.o sleep10.o sndrarp.o \
		sreset.o ssclock.o suspend.o \
		tdump.o test.o ttycntl.o ttygetc.o \
		ttyiin.o ttyinit.o ttyint.o ttyoin.o ttyopen.o \
		ttyputc.o ttyread.o ttywrite.o \
		udpecho.o udpnxtp.o udpsend.o unmount.o \
		unsleep.o userret.o \
		wait.o wakeup.o write.o \
		xdone.o \
		shell/x_bpool.o shell/x_cat.o shell/x_close.o shell/x_cp.o \
		shell/x_create.o shell/x_date.o shell/x_devs.o shell/x_dg.o \
		shell/x_echo.o shell/x_exit.o shell/x_help.o shell/x_kill.o \
		shell/x_mem.o shell/x_mount.o shell/x_mv.o shell/x_net.o \
		shell/x_ps.o shell/x_reboot.o shell/x_rf.o shell/x_rm.o shell/x_rls.o \
		shell/x_routes.o shell/x_sleep.o shell/x_snap.o \
		shell/x_unmou.o shell/x_uptime.o shell/x_who.o \
		shell/addarg.o shell/ascdate.o shell/login.o shell/lexan.o \
		shell/shell.o

DEPENDS:=	$(OBJS:.o=.d)

all:		a.h68

clean:
		rm -f $(OBJS) $(DEPENDS) a.out conf.c conf.h core make.out

a.out:		$(OBJS)
		$(LD) -S -e start -Ttext=0x00001000 -Tdata=0x00080000 $(OBJS) ../lib/libxc.a -L/opt/gnu/lib/gcc/m68k-none-elf/5.2.0/m68000 -lgcc

a.h68:		a.out
		$(OBJCOPY) -O srec a.out a.h68

conf.h:
		$(CONFIG)

conf.c:
		$(CONFIG)

conf.h:		xinu.conf
conf.c:		xinu.conf

%.d:		%.c
		env CC="$(CC)" sh Mkdeps.sh `dirname $<` $(CFLAGS) $< > $@

%.d:		%.s
		touch $@

include		$(DEPENDS)

#
# Makefile for Xinu shell and associated commands
#

.SUFFIXES:.o .c .s
DIR	=	/Users/cross/unix/project/xinu68k
BINDIR	=	$(DIR)/bin
CC	=	m68k-none-elf-gcc
CFLAGS	=	-O -c -I../../include -ansi -pedantic -std=c11 -Wall -Werror -nostdlib -nostartfiles -ffreestanding
AFLAGS	=	-u $(DIR)/include/sys.s
AS	=	m68k-none-elf-as
LD	=	m68k-none-elf-ld
AR	=	m68k-none-elf-ar
LORDER	=	m68k-none-elf-lorder
RANLIB	=	m68k-none-elf-ranlib
CPRINT	=	$(BINDIR)/cprint
SIZE	=	m68k-none-elf-size
LIB	=	$(DIR)/lib
.c.o:
		$(CC) $(CFLAGS)	$<
.s.o:
		$(CC) $(CFLAGS)	$<

CFILES=		addarg.c ascdate.c login.c lexan.c	\
		shell.c					\
		x_bpool.c x_cat.c x_close.c x_cp.c	\
		x_create.c x_date.c x_devs.c x_dg.c	\
		x_echo.c x_exit.c x_help.c x_kill.c	\
		x_mem.c x_mount.c x_mv.c x_net.c	\
		x_ps.c x_reboot.c x_rf.c x_rm.c x_rls.c	\
		x_routes.c x_sleep.c x_snap.c		\
		x_unmou.c x_uptime.c x_who.c

XOFILES=	x_bpool.o x_cat.o x_close.o x_cp.o	\
		x_create.o x_date.o x_devs.o x_dg.o	\
		x_echo.o x_exit.o x_help.o x_kill.o	\
		x_mem.o x_mount.o x_mv.o x_net.o	\
		x_ps.o x_reboot.o x_rf.o x_rm.o x_rls.o	\
		x_routes.o x_sleep.o x_snap.o		\
		x_unmou.o x_uptime.o x_who.o

HFILES=		shell.h cmd.h

all:		sh.o

sh.o:		addarg.o ascdate.o login.o lexan.o	\
		shell.o libS.a
		$(LD) -r -o sh.o \
			addarg.o ascdate.o login.o	\
			lexan.o shell.o libS.a

libS.a:		$(XOFILES)
		rm -rf libS.a
		$(AR) cr libS.a $(XOFILES)
		$(RANLIB) libS.a

install:	sh.o
		cp sh.o ..

clean:
		-rm -rf *.o ,* .,* core make.out *.a

everything:	all lint sizes xref

lint:		,lint

,lint:		$(CFILES)
		lint -n -I../../include $(CFILES) | Flint > ,lint

print:
		$(CPRINT) -c Cover *.h *.c

listings:	sizes xref
		$(CPRINT) -c Cover *.h *.c ,xref ,sizes ,ssizes Makefile

sizes:		,sizes ,ssizes

,sizes:		$(OFILES)
		$(SIZE) *.o > ,sizes

,ssizes:	$(CFILES) $(HFILES)
		./Dosizes

xref:		,xref

,xref:		,tags
		./Doxref

tags:		,tags

,tags:		$(CFILES) $(HFILES)
		ctags $(CFILES) $(HFILES)
		mv tags ,tags

depend:
		grep '^#include' *.c ../../include/*.h		\
		| sed	-e 's/</"..\/..\/h\//;s/>/"/'		\
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
addarg.o: ../../include/conf.h
addarg.o: ../../include/kernel.h
addarg.o: ../../include/proc.h
addarg.o: ../../include/shell.h
ascdate.o: ../../include/conf.h
ascdate.o: ../../include/kernel.h
ascdate.o: ../../include/date.h
lexan.o: ../../include/conf.h
lexan.o: ../../include/kernel.h
lexan.o: ../../include/shell.h
login.o: ../../include/conf.h
login.o: ../../include/kernel.h
login.o: ../../include/shell.h
shell.o: ../../include/conf.h
shell.o: ../../include/kernel.h
shell.o: ../../include/proc.h
shell.o: ../../include/shell.h
shell.o: ../../include/cmd.h
shell.o: ../../include/tty.h
x_bpool.o: ../../include/conf.h
x_bpool.o: ../../include/kernel.h
x_bpool.o: ../../include/mark.h
x_bpool.o: ../../include/bufpool.h
x_cat.o: ../../include/conf.h
x_cat.o: ../../include/kernel.h
x_close.o: ../../include/conf.h
x_close.o: ../../include/kernel.h
x_cp.o: ../../include/conf.h
x_cp.o: ../../include/kernel.h
x_create.o: ../../include/conf.h
x_create.o: ../../include/kernel.h
x_create.o: ../../include/a.out.h
x_date.o: ../../include/conf.h
x_date.o: ../../include/kernel.h
x_date.o: ../../include/sleep.h
x_date.o: ../../include/date.h
x_devs.o: ../../include/conf.h
x_devs.o: ../../include/kernel.h
x_dg.o: ../../include/conf.h
x_dg.o: ../../include/kernel.h
x_dg.o: ../../include/network.h
x_echo.o: ../../include/conf.h
x_echo.o: ../../include/kernel.h
x_exit.o: ../../include/conf.h
x_exit.o: ../../include/kernel.h
x_exit.o: ../../include/shell.h
x_help.o: ../../include/conf.h
x_help.o: ../../include/kernel.h
x_help.o: ../../include/shell.h
x_help.o: ../../include/cmd.h
x_kill.o: ../../include/conf.h
x_kill.o: ../../include/kernel.h
x_kill.o: ../../include/shell.h
x_mem.o: ../../include/conf.h
x_mem.o: ../../include/kernel.h
x_mem.o: ../../include/proc.h
x_mem.o: ../../include/mem.h
x_mount.o: ../../include/conf.h
x_mount.o: ../../include/kernel.h
x_mount.o: ../../include/io.h
x_mount.o: ../../include/name.h
x_mv.o: ../../include/conf.h
x_mv.o: ../../include/kernel.h
x_mv.o: ../../include/file.h
x_net.o: ../../include/conf.h
x_net.o: ../../include/kernel.h
x_net.o: ../../include/network.h
x_ps.o: ../../include/conf.h
x_ps.o: ../../include/kernel.h
x_ps.o: ../../include/proc.h
x_reboot.o: ../../include/conf.h
x_reboot.o: ../../include/kernel.h
x_rf.o: ../../include/conf.h
x_rf.o: ../../include/kernel.h
x_rf.o: ../../include/fserver.h
x_rf.o: ../../include/rfile.h
x_rls.o: ../../include/conf.h
x_rls.o: ../../include/kernel.h
x_rls.o: ../../include/shell.h
x_rm.o: ../../include/conf.h
x_rm.o: ../../include/kernel.h
x_rm.o: ../../include/file.h
x_routes.o: ../../include/conf.h
x_routes.o: ../../include/kernel.h
x_routes.o: ../../include/proc.h
x_routes.o: ../../include/network.h
x_sleep.o: ../../include/conf.h
x_sleep.o: ../../include/kernel.h
x_snap.o: ../../include/conf.h
x_snap.o: ../../include/kernel.h
x_snap.o: ../../include/core11.h
x_snap.o: ../../include/mem.h
x_unmou.o: ../../include/conf.h
x_unmou.o: ../../include/kernel.h
x_unmou.o: ../../include/io.h
x_unmou.o: ../../include/name.h
x_uptime.o: ../../include/conf.h
x_uptime.o: ../../include/kernel.h
x_uptime.o: ../../include/network.h
x_uptime.o: ../../include/rwho.h
x_who.o: ../../include/conf.h
x_who.o: ../../include/kernel.h
x_who.o: ../../include/date.h
x_who.o: ../../include/shell.h
../../include/disk.h: ../../include/xebec.h
../../include/disk.h: ../../include/dtc.h
../../include/lfile.h: ../../include/iblock.h
../../include/lfile.h: ../../include/file.h
../../include/network.h: ../../include/deqna.h
../../include/network.h: ../../include/ether.h
../../include/network.h: ../../include/ip.h
../../include/network.h: ../../include/icmp.h
../../include/network.h: ../../include/udp.h
../../include/network.h: ../../include/net.h
../../include/network.h: ../../include/dgram.h
../../include/network.h: ../../include/arp.h
../../include/network.h: ../../include/fserver.h
../../include/network.h: ../../include/rfile.h
../../include/network.h: ../../include/domain.h
../../include/rfile.h: ../../include/file.h
../../include/shell.h: ../../include/mark.h
#	DEPENDENCIES MUST END AT END OF	FILE
#	IF YOU PUT STUFF HERE IT WILL GO AWAY
#	see make depend	above

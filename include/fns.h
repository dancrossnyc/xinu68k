struct epacket;
struct dgblk;
struct dqsetup;
struct dreg;
struct dsblk;
struct devsw;
struct etblk;
struct flblk;
struct fphdr;
struct mblock;
struct pt;
struct tty;
struct xgram;

#include "disk.h"
#include "iblock.h"
#include "ip.h"

// access.c
SYSCALL access(char *name, int mode);
// adump.c
void adump(void);
// arp_in.c
int arp_in(struct epacket *packet, int device);
// arpfind.c
int arpfind(IPaddr faddr);
// arpinit.c
void arpinit(void);
// blkcopy.c
int blkcopy(char *to, char *from, int nbytes);
// blkequ.c
int blkequ(char *first, char *second, int nbytes);
// bpdump.c
int bpdump(void);
// chprio.c
SYSCALL chprio(int pid, int newprio);
// ckmode.c
int ckmode(char *mode);
// clkinit.c
void clkinit(void);
// close.c
SYSCALL close(int descrp);
// control.c
SYSCALL control(int descrp, int func, int addr);
// create.c
SYSCALL create(PROCESS(*procaddr) (), int ssize, int priority, char *name,
	       int nargs, ...);
// devdump.c
void devdump(void);
// dfalloc.c
int dfalloc(void);
// dfdsrch.c
struct fdes *dfdsrch(struct dsblk *dsptr, char *filenam, int mbits);
// dgalloc.c
int dgalloc(void);
// dgclose.c
int dgclose(struct devsw *devptr);
// dgcntl.c
int dgcntl(struct devsw *devptr, int func, int arg);
// dgdump.c
int dgdump(void);
// dginit.c
void dginit(struct devsw *devptr);
// dgmcntl.c
int dgmcntl(struct devsw *devptr, int func, char *addr);
// dgmopen.c
int dgmopen(struct devsw *devptr, char *forport, int locport);
// dgparse.c
int dgparse(struct dgblk *dgptr, char *fspec);
// dgread.c
int dgread(struct devsw *devptr, struct xgram *buff, int len);
// dgwrite.c
int dgwrite(struct devsw *devptr, struct xgram *buff, int len);
// dot2ip.c
void dot2ip(char *ip, int nad1, int nad2, int nad3, int nad4);
// dscntl.c
int dscntl(struct devsw *devptr, int func);
// dsinit.c
void dsinit(struct devsw *devptr);
// dsinter.c
INTPROC dsinter(struct dsblk *dsptr);
// dskbcpy.c
char *dskbcpy(void *oldbuf);
// dskenq.c
int dskenq(struct dreq *drptr, struct dsblk *dsptr);
// dskqopt.c
int dskqopt(struct dreq *p, struct dreq *q, struct dreq *drptr);
// dskstrt.c
void dskstrt(struct dsblk *dsptr);
// dsksync.c
int dsksync(struct devsw *devptr);
// dsopen.c
int dsopen(struct devsw *devptr, char *filenam, char *mode);
// dsread.c
int dsread(struct devsw *devptr, char *buff, DBADDR block);
// dsseek.c
int dsseek(struct devsw *devptr, DBADDR block);
// dswrite.c
int dswrite(struct devsw *devptr, char *buff, DBADDR block);
// dudir.c
int dudir(int diskdev);
// dumkfs.c
int dumkfs(int diskdev, int niblks, unsigned int nblocks, int diskid,
	   Bool verbose);
int dumkdl(int diskdev, DBADDR firstfb, DBADDR lastfb, Bool verbose);
int dumkil(int diskdev, int niblks, Bool verbose);
// ethinit.c
void ethinit(struct devsw *devptr);
// ethinter.c
INTPROC ethinter(struct etblk *etptr);
// ethread.c
int ethread(struct devsw *devptr, char *buff, int len);
// ethrstrt.c
int ethrstrt(struct etblk *etptr, char *buf, int len);
// ethstrt.c
int ethstrt(struct etblk *etptr, struct dqsetup *setup);
// ethwrite.c
int ethwrite(struct devsw *devptr, char *buff, int len);
// ethwstrt.c
void ethwstrt(struct etblk *etptr, char *buf, int len, int setup);
// freebuf.c
SYSCALL freebuf(void *buf);
// freemem.c
SYSCALL freemem(void *block, size_t size);
// getaddr.c
SYSCALL getaddr(IPaddr address);
// getbuf.c
void *getbuf(int poolid);
// getc.c
SYSCALL getc(int descrp);
// getitem.c
int getfirst(int head);
int getlast(int tail);
// getmem.c
SYSCALL *getmem(size_t nbytes);
// getname.c
SYSCALL getname(char *nam);
// getnet.c
SYSCALL getnet(IPaddr address);
// getpath.c
int getpath(IPaddr faddr);
// getpid.c
SYSCALL getpid(void);
// getprio.c
SYSCALL getprio(int pid);
// getstk.c
SYSCALL *getstk(size_t nbytes);
// gettime.c
SYSCALL gettime(long *timvar);
// getutim.c
SYSCALL getutim(long *timvar);
// ibclear.c
void ibclear(struct iblk *ibptr, long ibbyte);
// ibfree.c
int ibfree(int diskdev, IBADDR inum);
// ibget.c
void ibget(int diskdev, IBADDR inum, struct iblk *loc);
// iblfree.c
int iblfree(int diskdev, IBADDR iblist);
// ibnew.c
int ibnew(int diskdev, int writedir);
// ibput.c
int ibput(int diskdev, IBADDR inum, struct iblk *loc);
// icmp_in.c
int icmp_in(struct epacket *packet, int icmpp, int lim);
// init.c
int init(int descrp);
// initialize.c
int nulluser(void);
// insert.c
int insert(int proc, int head, int key);
// insertd.c
int insertd(int pid, int head, int key);
// intr.s
int disable(void);
void enable(void);
void restore(int sr);
// ioerr.c
int ioerr(void);
INTPROC interr(void);
// ioinit.c
int ioinit(int descrp);
int iosetvec(int descrp, void *incode, void *outcode);
// ionull.c
int ionull(void);
void initnull(void);
// ip2name.c
SYSCALL ip2name(IPaddr ip, char *nam);
// ip_in.c
int ip_in(struct epacket *packet, int icmpp, int lim);
// ipsend.c
int ipsend(IPaddr faddr, struct epacket *packet, int datalen);
// kill.c
SYSCALL kill(int pid);
// kprintf.c
int kprintf(const char *fmt, ...);
// lfclose.c
int lfclose(struct devsw *devptr);
// lfgetc.c
int lfgetc(struct devsw *devptr);
// lfinit.c
void lfinit(struct devsw *devptr);
// lfputc.c
int lfputc(struct devsw *devptr, int ch);
// lfread.c
int lfread(struct devsw *devptr, char *buff, int count);
// lfsdfree.c
int lfsdfree(int diskdev, DBADDR dba);
// lfseek.c
int lfseek(struct devsw *devptr, long offset);
// lfsetup.c
void lfsetup(int diskdev, struct flblk *flptr);
// lfsflush.c
int lfsflush(struct flblk *flptr);
// lfsnewd.c
int lfsnewd(int diskdev, struct flblk *flptr);
// lfwrite.c
int lfwrite(struct devsw *devptr, char *buff, int count);
// mark.c
void _mkinit(void);
SYSCALL mark(int *loc);
// mdump.c
void mdump(void);
// mkarp.c
struct epacket *mkarp(int typ, int op, IPaddr spaddr, IPaddr tpaddr);
// mkpool.c
SYSCALL mkpool(int bufsiz, int numbufs);
// mount.c
SYSCALL mount(char *prefix, int dev, char *replace);
// naminit.c
void naminit(void);
// namemap.c
SYSCALL namemap(char *name, char *newname);
// namopen.c
int namopen(struct devsw *devptr, char *filenam, char *mode);
// namrepl.c
SYSCALL namrepl(char *name, char *newname);
// ndump.c
void ndump(void);
// netdump.c
int netdump(void);
// netin.c
PROCESS netin(int userpid);
// netinit.c
int netinit(void);
// netnum.c
int netnum(IPaddr netpart, IPaddr address);
// netout.c
PROCESS netout(int userpid, int icmpp);
// newqueue.c
int newqueue(void);
// nqalloc.c
int nqalloc(void);
// open.c
SYSCALL open(int descrp, char *nam, char *mode);
// pcount.c
SYSCALL pcount(int portid);
// pcreate.c
SYSCALL pcreate(int count);
// pdelete.c
SYSCALL pdelete(int portid, int (*dispose) (void *));
// pinit.c
SYSCALL pinit(int maxmsgs);
// poolinit.c
int poolinit(void);
// prdump.c
void prdump(void);
void prdumph(void);
void prdumpa(void);
// preceive.c
SYSCALL preceive(int portid);
// preset.c
SYSCALL preset(int portid, int (*dispose) (void *));
// psend.c
SYSCALL psend(int portid, uword msg);
// ptclear.c
void _ptclear(struct pt *ptptr, int newstate, int (*dispose) (void *));
// putc.c
SYSCALL putc(int descrp, int ch);
// qdump.c
void qdump(void);
void qdumph(void);
void qdumpa(void);
// queue.c
int enqueue(int item, int tail);
int dequeue(int item);
// rarp_in.c
int rarp_in(struct epacket *packet, int device);
// read.c
SYSCALL read(int descrp, void *buff, int count);
// ready.c
int ready(int pid);
int readysched(int pid);
// receive.c
SYSCALL receive(void);
// recvclr.c
SYSCALL recvclr(void);
// recvtim.c
SYSCALL recvtim(int maxwait);
// remove.c
SYSCALL remove(char *name, int key);
// rename.c
SYSCALL rename(char *old, char *new);
// resched.c
int resched(void);
// resume.c
SYSCALL resume(int pid);
// rfalloc.c
int rfalloc(void);
// rfclose.c
int rfclose(struct devsw *devptr);
// rfcntl.c
int rfcntl(struct devsw *devptr, int func, char *addr, char *addr2);
// rfdump.c
void rfdump(void);
// rfgetc.c
int rfgetc(struct devsw *devptr);
// rfinit.c
void rfinit(struct devsw *devptr);
// rfio.c
int rfio(struct devsw *devptr, int rop, char *buff, int len);
// rfmkpac.c
int rfmkpac(int rop, char *rname, long *rpos, char *buff, int len);
// rfopen.c
int rfopen(struct devsw *devptr, char *name, char *mode);
// rfputc.c
int rfputc(struct devsw *devptr, int ch);
// rfread.c
int rfread(struct devsw *devptr, char *buff, int len);
// rfseek.c
int rfseek(struct devsw *devptr, long offset);
// rfsend.c
int rfsend(struct fphdr *fptr, int reqlen, int rplylen);
// rfwrite.c
int rfwrite(struct devsw *devptr, char *buff, int len);
// route.c
int route(IPaddr faddr, struct epacket *packet, int totlen);
// rwho.c
void rwho(void);
// rwhod.c
PROCESS rwhod(void);
// rwhoind.c
PROCESS rwhoind(void);
// scount.c
SYSCALL scount(int sem);
// screate.c
SYSCALL screate(int count);
// sdelete.c
SYSCALL sdelete(int sem);
// seek.c
SYSCALL seek(int descrp, long pos);
// send.c
SYSCALL send(int pid, int msg);
// sendf.c
SYSCALL sendf(int pid, int msg);
// setdev.c
SYSCALL setdev(int pid, int dev1, int dev2);
// setnok.c
SYSCALL setnok(int nok, int pid);
// signal.c
SYSCALL signal(int sem);
// signaln.c
SYSCALL signaln(int sem, int count);
// sleep.c
SYSCALL sleep(int n);
// sleep10.c
SYSCALL sleep10(int n);
// sndrarp.c
int sndrarp(void);
// sreset.c
SYSCALL sreset(int sem, int count);
// ssclock.c
void stopclk(void);
void strtclk(void);
// suspend.c
SYSCALL suspend(int pid);
// tdump.c
void tdump(void);
void tdumph(void);
void tdump1(int tnum);
// test.c
int main(void);
// ttycntl.c
int ttycntl(struct devsw *devptr, int func);
// ttygetc.c
int ttygetc(struct devsw *devptr);
// ttyiin.c
INTPROC ttyiin(struct tty *iptr);
// ttyinit.c
void ttyinit(struct devsw *devptr);
// ttyoin.c
INTPROC ttyoin(struct tty *iptr);
// ttyopen.c
int ttyopen(struct devsw *devptr, char *nam, char *mode);
// ttyputc.c
int ttyputc(struct devsw *devptr, int ch);
// ttyread.c
int ttyread(struct devsw *devptr, char *buff, int count);
// ttywrite.c
int ttywrite(struct devsw *devptr, char *buff, int count);
// udpecho.c
PROCESS udpecho(void);
// udpnxtp.c
int udpnxtp(void);
// udpsend.c
int udpsend(IPaddr faddr, int fport, int lport, struct epacket *packet,
	    int datalen);
// unmount.c
SYSCALL unmount(char *prefix);
// unsleep.c
SYSCALL unsleep(int pid);
// userret.c
void userret(void);
// wait.c
SYSCALL wait(int sem);
// wakeup.c
INTPROC wakeup(void);
// write.c
SYSCALL write(int descrp, const void *buff, int count);
// xdone.c
void xdone(void);

int login(int dev);
int shell(int dev);

void setclkr(void);
void panic(const char *);
void ctxsw(uword *, uword *);
void restart(void);

// Shell.
// addarg.c
int addarg(int pid, int nargs, int len);
// ascdate.c
int ascdate(long time, char *str);
// lexan.c
int lexan(char *line);
// login.c
int login(int dev);
// shell.c
int shell(int dev);
// x_bpool.c
int x_bpool(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_cat.c
int x_cat(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_close.c
int x_close(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_cp.c
int x_cp(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_create.c
int x_creat(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_date.c
int x_date(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_devs.c
int x_devs(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_dg.c
int x_dg(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_echo.c
int x_echo(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_exit.c
int x_exit(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_help.c
int x_help(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_kill.c
int x_kill(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_mem.c
int x_mem(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_mount.c
int x_mount(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_mv.c
int x_mv(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_net.c
int x_net(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_ps.c
int x_ps(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_reboot.c
int x_reboot(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_rf.c
int x_rf(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_rls.c
int x_rls(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_rm.c
int x_rm(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_routes.c
int x_routes(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_sleep.c
int x_sleep(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_snap.c
int x_snap(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_unmou.c
int x_unmou(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_uptime.c
int x_uptime(int stdin, int stdout, int stderr, int nargs, char *args[]);
// x_who.c
int x_who(int stdin, int stdout, int stderr);

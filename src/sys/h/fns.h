#include "disk.h"
#include "iblock.h"
#include "ip.h"

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

/* access.c */
SYSCALL access(char *name, int mode);
/* adump.c */
void adump(void);
/* arp_in.c */
int arp_in(struct epacket *packet, int device);
/* arpfind.c */
int arpfind(IPaddr faddr);
/* arpinit.c */
void arpinit(void);
/* blkcopy.c */
int blkcopy(char *to, char *from, int nbytes);
/* blkequ.c */
int blkequ(char *first, char *second, int nbytes);
/* bpdump.c */
int bpdump(void);
/* chprio.c */
SYSCALL chprio(int pid, int newprio);
/* ckmode.c */
int ckmode(char *mode);
/* clkinit.c */
void clkinit(void);
/* close.c */
SYSCALL close(int descrp);
/* control.c */
SYSCALL control(int descrp, int func, char *addr, char *addr2);
/* create.c */
SYSCALL create(int procaddr, int ssize, int priority, char *name, int nargs, int args);
/* devdump.c */
void devdump(void);
/* dfalloc.c */
int dfalloc(void);
/* dfdsrch.c */
struct fdes *dfdsrch(struct dsblk *dsptr, char *filenam, int mbits);
/* dgalloc.c */
int dgalloc(void);
/* dgclose.c */
int dgclose(struct devsw *devptr);
/* dgcntl.c */
int dgcntl(struct devsw *devptr, int func, int arg);
/* dgdump.c */
int dgdump(void);
/* dginit.c */
int dginit(struct devsw *devptr);
/* dgmcntl.c */
int dgmcntl(struct devsw *devptr, int func, char *addr);
/* dgmopen.c */
int dgmopen(struct devsw *devptr, char *forport, int locport);
/* dgparse.c */
int dgparse(struct dgblk *dgptr, char *fspec);
/* dgread.c */
int dgread(struct devsw *devptr, struct xgram *buff, int len);
/* dgwrite.c */
int dgwrite(struct devsw *devptr, struct xgram *buff, int len);
/* dot2ip.c */
int dot2ip(char *ip, int nad1, int nad2, int nad3, int nad4);
/* dscntl.c */
int dscntl(struct devsw *devptr, int func);
/* dsinit.c */
int dsinit(struct devsw *devptr);
/* dsinter.c */
INTPROC dsinter(struct dsblk *dsptr);
/* dskbcpy.c */
char *dskbcpy(char *oldbuf);
/* dskenq.c */
int dskenq(struct dreq *drptr, struct dsblk *dsptr);
/* dskqopt.c */
int dskqopt(struct dreq *p, struct dreq *q, struct dreq *drptr);
/* dskstrt.c */
void dskstrt(struct dsblk *dsptr);
/* dsksync.c */
int dsksync(struct devsw *devptr);
/* dsopen.c */
int dsopen(struct devsw *devptr, char *filenam, char *mode);
/* dsread.c */
int dsread(struct devsw *devptr, char *buff, DBADDR block);
/* dsseek.c */
int dsseek(struct devsw *devptr, DBADDR block);
/* dswrite.c */
int dswrite(struct devsw *devptr, char *buff, DBADDR block);
/* dudir.c */
int dudir(int diskdev);
/* dumkfs.c */
int dumkfs(int diskdev, int niblks, unsigned int nblocks, int diskid, Bool verbose);
int dumkdl(int diskdev, DBADDR firstfb, DBADDR lastfb, Bool verbose);
int dumkil(int diskdev, int niblks, Bool verbose);
/* ethinit.c */
int ethinit(struct devsw *devptr);
/* ethinter.c */
INTPROC ethinter(struct etblk *etptr);
/* ethread.c */
int ethread(struct devsw *devptr, char *buff, int len);
/* ethrstrt.c */
int ethrstrt(struct etblk *etptr, char *buf, int len);
/* ethstrt.c */
int ethstrt(struct etblk *etptr, struct dqsetup *setup);
/* ethwrite.c */
int ethwrite(struct devsw *devptr, char *buff, int len);
/* ethwstrt.c */
int ethwstrt(struct etblk *etptr, char *buf, int len, int setup);
/* freebuf.c */
SYSCALL freebuf(int *buf);
/* freemem.c */
SYSCALL freemem(struct mblock *block, unsigned size);
/* getaddr.c */
SYSCALL getaddr(IPaddr address);
/* getbuf.c */
SYSCALL *getbuf(int poolid);
/* getc.c */
SYSCALL getc(int descrp);
/* getitem.c */
int getfirst(int head);
int getlast(int tail);
/* getmem.c */
SYSCALL *getmem(unsigned nbytes);
/* getname.c */
SYSCALL getname(char *nam);
/* getnet.c */
SYSCALL getnet(IPaddr address);
/* getpath.c */
int getpath(IPaddr faddr);
/* getpid.c */
SYSCALL getpid(void);
/* getprio.c */
SYSCALL getprio(int pid);
/* getstk.c */
SYSCALL *getstk(unsigned int nbytes);
/* gettime.c */
SYSCALL gettime(long *timvar);
/* getutim.c */
SYSCALL getutim(long *timvar);
/* ibclear.c */
int ibclear(struct iblk *ibptr, long ibbyte);
/* ibfree.c */
int ibfree(int diskdev, IBADDR inum);
/* ibget.c */
int ibget(int diskdev, IBADDR inum, struct iblk *loc);
/* iblfree.c */
int iblfree(int diskdev, IBADDR iblist);
/* ibnew.c */
int ibnew(int diskdev, int writedir);
/* ibput.c */
int ibput(int diskdev, IBADDR inum, struct iblk *loc);
/* icmp_in.c */
int icmp_in(struct epacket *packet, int icmpp, int lim);
/* init.c */
int init(int descrp);
/* initialize.c */
int nulluser(void);
/* insert.c */
int insert(int proc, int head, int key);
/* insertd.c */
int insertd(int pid, int head, int key);
/* ioerr.c */
int ioerr(void);
/* ioinit.c */
int ioinit(int descrp);
int iosetvec(int descrp, int incode, int outcode);
/* ionull.c */
int ionull(void);
/* ip2name.c */
SYSCALL ip2name(IPaddr ip, char *nam);
/* ip_in.c */
int ip_in(struct epacket *packet, int icmpp, int lim);
/* ipsend.c */
int ipsend(IPaddr faddr, struct epacket *packet, int datalen);
/* kill.c */
SYSCALL kill(int pid);
/* kprintf.c */
int kprintf(char *fmt, ...);
/* lfclose.c */
int lfclose(struct devsw *devptr);
/* lfgetc.c */
int lfgetc(struct devsw *devptr);
/* lfinit.c */
int lfinit(struct devsw *devptr);
/* lfputc.c */
int lfputc(struct devsw *devptr, int ch);
/* lfread.c */
int lfread(struct devsw *devptr, char *buff, int count);
/* lfsdfree.c */
int lfsdfree(int diskdev, DBADDR dba);
/* lfseek.c */
int lfseek(struct devsw *devptr, long offset);
/* lfsetup.c */
int lfsetup(int diskdev, struct flblk *flptr);
/* lfsflush.c */
int lfsflush(struct flblk *flptr);
/* lfsnewd.c */
int lfsnewd(int diskdev, struct flblk *flptr);
/* lfwrite.c */
int lfwrite(struct devsw *devptr, char *buff, int count);
/* mark.c */
int _mkinit(void);
SYSCALL mark(int *loc);
/* mdump.c */
int mdump(void);
/* mkarp.c */
struct epacket *mkarp(int typ, int op, IPaddr spaddr, IPaddr tpaddr);
/* mkpool.c */
SYSCALL mkpool(int bufsiz, int numbufs);
/* mount.c */
SYSCALL mount(char *prefix, int dev, char *replace);
/* naminit.c */
int naminit(void);
/* nammap.c */
SYSCALL nammap(char *name, char *newname);
/* namopen.c */
int namopen(struct devsw *devptr, char *filenam, char *mode);
/* namrepl.c */
SYSCALL namrepl(char *name, char *newname);
/* ndump.c */
int ndump(void);
/* netdump.c */
int netdump(void);
/* netin.c */
PROCESS netin(int userpid);
/* netinit.c */
int netinit(void);
/* netnum.c */
int netnum(IPaddr netpart, IPaddr address);
/* netout.c */
PROCESS netout(int userpid, int icmpp);
/* newqueue.c */
int newqueue(void);
/* nqalloc.c */
int nqalloc(void);
/* open.c */
SYSCALL open(int descrp, char *nam, char *mode);
/* pcount.c */
SYSCALL pcount(int portid);
/* pcreate.c */
SYSCALL pcreate(int count);
/* pdelete.c */
SYSCALL pdelete(int portid, int (*dispose)(void));
/* pinit.c */
SYSCALL pinit(int maxmsgs);
/* poolinit.c */
int poolinit(void);
/* prdump.c */
int prdump(void);
int prdumph(void);
int prdumpa(void);
/* preceive.c */
SYSCALL preceive(int portid);
/* preset.c */
SYSCALL preset(int portid, int (*dispose)(void));
/* psend.c */
SYSCALL psend(int portid, int msg);
/* ptclear.c */
int _ptclear(struct pt *ptptr, int newstate, int (*dispose)(void));
/* putc.c */
SYSCALL putc(int descrp, int ch);
/* qdump.c */
int qdump(void);
int qdumph(void);
int qdumpa(void);
/* queue.c */
int enqueue(int item, int tail);
int dequeue(int item);
/* rarp_in.c */
int rarp_in(struct epacket *packet, int device);
/* read.c */
SYSCALL read(int descrp, char *buff, int count);
/* ready.c */
int ready(int pid, int resch);
/* receive.c */
SYSCALL receive(void);
/* recvclr.c */
SYSCALL recvclr(void);
/* recvtim.c */
SYSCALL recvtim(int maxwait);
/* remove.c */
SYSCALL remove(char *name, int key);
/* rename.c */
SYSCALL rename(char *old, char *new);
/* resched.c */
int resched(void);
/* resume.c */
SYSCALL resume(int pid);
/* rfalloc.c */
int rfalloc(void);
/* rfclose.c */
int rfclose(struct devsw *devptr);
/* rfcntl.c */
int rfcntl(struct devsw *devptr, int func, char *addr, char *addr2);
/* rfdump.c */
int rfdump(void);
/* rfgetc.c */
int rfgetc(struct devsw *devptr);
/* rfinit.c */
int rfinit(struct devsw *devptr);
/* rfio.c */
int rfio(struct devsw *devptr, int rop, char *buff, int len);
/* rfmkpac.c */
int rfmkpac(int rop, char *rname, long *rpos, char *buff, int len);
/* rfopen.c */
int rfopen(struct devsw *devptr, char *name, char *mode);
/* rfputc.c */
int rfputc(struct devsw *devptr, int ch);
/* rfread.c */
int rfread(struct devsw *devptr, char *buff, int len);
/* rfseek.c */
int rfseek(struct devsw *devptr, long offset);
/* rfsend.c */
int rfsend(struct fphdr *fptr, int reqlen, int rplylen);
/* rfwrite.c */
int rfwrite(struct devsw *devptr, char *buff, int len);
/* route.c */
int route(IPaddr faddr, struct epacket *packet, int totlen);
/* rwho.c */
int rwho(void);
/* rwhod.c */
PROCESS rwhod(void);
/* rwhoind.c */
PROCESS rwhoind(void);
/* scount.c */
SYSCALL scount(int sem);
/* screate.c */
SYSCALL screate(int count);
/* sdelete.c */
SYSCALL sdelete(int sem);
/* seek.c */
SYSCALL seek(int descrp, long pos);
/* send.c */
SYSCALL send(int pid, int msg);
/* sendf.c */
SYSCALL sendf(int pid, int msg);
/* setdev.c */
SYSCALL setdev(int pid, int dev1, int dev2);
/* setnok.c */
SYSCALL setnok(int nok, int pid);
/* signal.c */
SYSCALL signal(int sem);
/* signaln.c */
SYSCALL signaln(int sem, int count);
/* sleep.c */
SYSCALL sleep(int n);
/* sleep10.c */
SYSCALL sleep10(int n);
/* sndrarp.c */
int sndrarp(void);
/* sreset.c */
SYSCALL sreset(int sem, int count);
/* ssclock.c */
int stopclk(void);
int strtclk(void);
/* suspend.c */
SYSCALL suspend(int pid);
/* tdump.c */
int tdump(void);
int tdumph(void);
int tdump1(int tnum);
/* test.c */
int main(void);
/* ttycntl.c */
int ttycntl(struct devsw *devptr, int func);
/* ttygetc.c */
int ttygetc(struct devsw *devptr);
/* ttyiin.c */
INTPROC ttyiin(struct tty *iptr);
/* ttyinit.c */
int ttyinit(struct devsw *devptr);
/* ttyoin.c */
INTPROC ttyoin(struct tty *iptr);
/* ttyopen.c */
int ttyopen(struct devsw *devptr, char *nam, char *mode);
/* ttyputc.c */
int ttyputc(struct devsw *devptr, int ch);
/* ttyread.c */
int ttyread(struct devsw *devptr, char *buff, int count);
/* ttywrite.c */
int ttywrite(struct devsw *devptr, char *buff, int count);
/* udpecho.c */
PROCESS udpecho(void);
/* udpnxtp.c */
int udpnxtp(void);
/* udpsend.c */
int udpsend(IPaddr faddr, int fport, int lport, struct epacket *packet, int datalen);
/* unmount.c */
SYSCALL unmount(char *prefix);
/* unsleep.c */
SYSCALL unsleep(int pid);
/* userret.c */
int userret(void);
/* wait.c */
SYSCALL wait(int sem);
/* wakeup.c */
INTPROC wakeup(void);
/* write.c */
SYSCALL write(int descrp, char *buff, int count);
/* xdone.c */
int xdone(void);

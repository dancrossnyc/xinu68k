/* Close.c */
int Close(int rfd);
/* Open.c */
int Open(char *name, int mode);
/* Seek.c */
int Seek(int rfd, long newpos);
/* Uncache.c */
int Uncache(char *name);
/* fgetargs.c */
int fgetargs(int argc, char *argv[]);
int fexit(void);
/* fgetreq.c */
int fgetreq(int sock, struct fpacket *fpacptr, struct sockaddr *fromptr, int *fromlen);
/* finit.c */
int finit(int argc, char *argv[]);
/* fmode.c */
int fmode(int xmode);
/* fs.c */
int main(int argc, char *argv[]);
/* fsaccess.c */
int fsaccess(struct fpacket *fpacptr, int flen);
/* fsclose.c */
int fsclose(struct fpacket *fpacptr, int flen);
/* fsmkdir.c */
int fsmkdir(struct fpacket *fpacptr, int flen);
/* fsndrply.c */
int fsndrply(int s, struct fpacket *fptr, int len, struct sockaddr *toaddr, int tolen);
/* fsopen.c */
int fsopen(struct fpacket *fpacptr, int flen);
/* fsread.c */
int fsread(struct fpacket *fpacptr, int flen);
/* fsrename.c */
int fsrename(struct fpacket *fpacptr, int flen);
/* fsrmdir.c */
int fsrmdir(struct fpacket *fpacptr, int flen);
/* fstrans.c */
int fstrans(struct fpacket *fpacptr, int flen);
/* fsunlink.c */
int fsunlink(struct fpacket *fpacptr, int flen);
/* fswrite.c */
int fswrite(struct fpacket *fpacptr, int flen);
/* openfile.c */
int openfile(char *name, int xmode);
/* rmfile.c */
int rmfile(char *name);

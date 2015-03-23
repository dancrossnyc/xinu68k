
/* 
 * bed.c - BED (back end daemon) process for distributed odt/download
 * 
 * Author:	Jim Griffioen/Shawn Oosterman
 * 		Dept. of Computer Sciences
 * 		Purdue University
 * Date:	Thu Jun  9 10:30:50 1988
 *
 * Copyright (c) 1988 Jim Griffioen/Shawn Oosterman
 */

#include <stdio.h>
#include <sys/wait.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/file.h>

#include "../h/utils.h"
#include "../h/bed.h"
#include "../h/bmutils.h"
#include "../h/netutils.h"
#include "../h/bedata.h"



int sock;				/* backend daemon socket	*/
int pidodt;
struct odtdata **mdata;			/* machines/odt data structure	*/
int becount;				/* number of backend machines	*/
char machinename[MAXMACHINENAME];	/* name of this machine		*/
struct statresp configstatus;		/* configuration status		*/
	

#define BACKGROUND


/*
 *---------------------------------------------------------------------------
 * main (csb, rgsb) -- fork process in background and wait for requests.
 *---------------------------------------------------------------------------
 */
main (csb, rgsb)
int csb;
char *rgsb[];
{
	struct sockaddr_in sa;		/* sock addr of incoming dgram	*/
	int lsaT = lsa;			/* size of sa			*/
	int c;				/* count of bytes received	*/
	struct bm bm;			/* buffer for incoming datagram	*/
	union wait status;		/* wait status			*/
	int pid;			/* pid returned from wait	*/
	char directory[256];		/* directory that must exits	*/

	/* make sure all the necessary directories and files are there */
	strcpy(directory, BASEDIR);
	directory[strlen(directory)-1] = '\0';	/* remove the backslash */
	if (access(directory, F_OK) != 0) {
		if (mkdir(directory, 0777) != 0) {
			fprintf("directory '%s' not found\n", directory);
			exit(1);
		}
	}
	if (access(IN_FILE, F_OK) != 0) {
		fprintf("configuration file '%s' missing\n", IN_FILE);
		exit(1);
	}
	
#ifdef BACKGROUND
	if (fork() > 0) {
		exit(0);		/* grandparent exits		*/
	}
#endif

	
restart:
	if (fork () > 0) {		/* parent monitors child and	*/
		pid = wait(&status);	/* restarts the child (bed) if	*/
					/* it dies for some reason	*/
		if (status.w_T.w_Retcode == REALLYDIE) {
			Log("bed killed by 'bedkill' command");
			exit(1);
		}
		if (status.w_T.w_Retcode == RESTART) { /*restart from scratch*/
			execl(BED_EXEC_PATH,"bed",0);
			SysError("Can't reboot, execl failed");
		}
		goto restart;		/* it dies for some reason	*/
	}
	
	sock = ListenUdp (KNOWN_UDP_PORT);

	Log ("bed restarted");
	
	readodtdata(&mdata, &becount);	/* read machines database	*/
	if (gethostname(machinename, MAXDETAIL) != 0) {	/* get mach name*/
		Log("Error getting host name\n");
		strcpy(machinename, "unknown");
	}
	makestatus(&configstatus);	/* fill in configuration status	*/
	
	for (;;) {
		c = bmrecvfrom (sock, &bm, lbm, 0, &sa, &lsaT);
		if (c == lbm)
		    ProcessRequest (&sa, &bm);
		else
		    BedReply (&sa, RESP_ERR, "wrong size request structure");
	}
}

/*
 *---------------------------------------------------------------------------
 * IsBogus (pbm) -- return error message if pbm is bogus.
 *---------------------------------------------------------------------------
 */
char *IsBogus (pbm)
 struct bm *pbm;
{
	if (pbm->ver != CURVER)
	    return "version incorrect";
	return NULL;
}


/*
 *---------------------------------------------------------------------------
 * ProcessRequest (psa, pbm) -- process the network request
 *---------------------------------------------------------------------------
 */
ProcessRequest (psa, pbm)
struct sockaddr_in *psa;
struct bm *pbm;
{
	char *sb;
	char msg[MAXDETAIL];
	struct lockreq *lreq;
	char cuser[MAXUID];		/* current user			*/
	char chost[MAXMACHINENAME];	/* current host of user		*/
	char cbemachine[MAXMACHINENAME]; /* for current backend machine	*/
	char cidletime[IDLELEN];	/* idle time for current bend	*/
	struct genericreq *req;		/* generic request structure	*/
	struct odtdata *beconfig;	/* backend configuration details*/

    
	if (sb = IsBogus (pbm)) {
		strcpy(msg, sb);
		BedReply (psa, RESP_ERR, msg);
		return;
	}
	
	switch (atoi(pbm->cmd)) {
	      case REQ_QUIT:
		strcpy(msg, machinename);
		BedReply (psa, RESP_OK, msg);
		Quit();
		break;
	      case REQ_REBOOT:
		strcpy(msg, "rebooting");
		BedReply (psa, RESP_OK, msg);
		Reboot();
		break;
	      case REQ_STATUS:
		makestatus((struct statresp *) msg);
		BedReply (psa, RESP_OK, msg);
		break;
	      case REQ_ODT_CONNECT:
		req = (struct genericreq *) pbm->detail;
		checklock(cuser, chost, req->bename, cidletime);
		if (strcmp(cuser, req->uid) == 0) {
			touchlock(req->bename);
			beconfig = getbeconfig(mdata, becount, req->bename);
			if (beconfig == NULL) {
				strcpy(msg, "can't find backend");
				BedReply(psa, RESP_ERR, msg);
				break;
			}
			if ((pidodt = fork()) == 0)
			    odtd(psa, sock, beconfig);
		}
		else {
			strcpy(msg, "no privilage");
			BedReply(psa, RESP_ERR, msg);
		}
		break;
	      case REQ_DNLD_CONNECT:
		req = (struct genericreq *) pbm->detail;
		checklock(cuser, chost, req->bename, cidletime);
		if (strcmp(cuser, req->uid) == 0) {
			touchlock(req->bename);
			beconfig = getbeconfig(mdata, becount, req->bename);
			if (beconfig == NULL) {
				strcpy(msg, "can't find backend");
				BedReply(psa, RESP_ERR, msg);
				break;
			}
			if ((pidodt = fork()) == 0)
			    downloadd(psa, sock, beconfig);
		}
		else {
			strcpy(msg, "no privilage");
			BedReply(psa, RESP_ERR, msg);
		}
		break;
	      case REQ_LOCK:
		lreq = (struct lockreq *) pbm->detail;
		if (getlock(lreq->uid, lreq->hostid, lreq->bename) == SYSOK) {
			BedReply (psa, RESP_OK, (char *)lreq);
		}
		else {
			BedReply (psa, RESP_LOCK_REFUSED, (char *)lreq);
		}
		break;
	      case REQ_UNLOCK:
		lreq = (struct lockreq *) pbm->detail;
		if (unlock(lreq->bename) == SYSOK) {
			BedReply (psa, RESP_OK, (char *)lreq);
		}
		else {
			BedReply (psa, RESP_ERR, (char *)lreq);
		}
		break;
	      default:
		strcpy(msg, "invalid command");
		BedReply (psa, RESP_ERR, msg);
		break;
	}
}

/* 
 *---------------------------------------------------------------------------
 * BedReply -- build and send bm
 *---------------------------------------------------------------------------
*/
BedReply (psa, resp, detail)
struct sockaddr_in *psa;
int resp;
char *detail;
{
	struct bm bm;
	
	bm.ver = CURVER;
	sprintf(bm.cmd, "%d", resp);
	bcopy (detail, bm.detail, MAXDETAIL);

	if (bmsendto (sock, &bm, lbm, 0, psa, lsa) <= 0)
	    SysError ("sendto");
	
}

/*
 *---------------------------------------------------------------------------
 * Quit - kill backend daemon
 *---------------------------------------------------------------------------
 */
Quit()
{
	CleanUp();
	exit(REALLYDIE);		/* tell monitoring process	*/
					/* not to restart the bed	*/
}

/*
 *---------------------------------------------------------------------------
 * makestatus - get status and fill in status message contents
 *---------------------------------------------------------------------------
 */
makestatus(stats)
struct statresp *stats;
{
	char buf[MAXDETAIL];		/* temporary character string	*/
	int i;				/* counter variable		*/
	struct odtdata *machdata;	/* machines/odt data structure	*/
	char user[MAXUID];		/* user who has the machine	*/
	char host[MAXMACHINENAME];	/* host the user is on		*/
	char idletime[IDLELEN];		/* len of idle time string	*/
	double ldaver[5];		/* load averages		*/

	strcpy(stats->festatus.fename, machinename);
	sprintf(buf, "%d", getnumusers());
	strcpy(stats->festatus.numusers, buf);
	sprintf(buf, "%d", becount);
	strcpy(stats->festatus.numbends, buf);
	getloadaver(ldaver);
	sprintf(buf, "%6.2f %6.2f %6.2f", ldaver[0], ldaver[1], ldaver[2]);
	strcpy(stats->festatus.loadav, buf);
	for (i = 0; i < becount; i++) {
		machdata = mdata[i];
		strcpy(stats->bestatus[i].bename, machdata->bename);
		strcpy(stats->bestatus[i].ttyname, machdata->sline);
		strcpy(stats->bestatus[i].class, machdata->class);
		checklock(user, host, machdata->bename, idletime);
		strcpy(stats->bestatus[i].idle, idletime);
		strcpy(stats->bestatus[i].user, user);
	}
}


/*
 *---------------------------------------------------------------------------
 * Reboot - restart the backend daemon
 *---------------------------------------------------------------------------
 */
Reboot()
{
	CleanUp();
	exit(RESTART);			/* parent will restart the BED	*/
}

/*
 *---------------------------------------------------------------------------
 * Cleanup - Clean things up a bit before exiting
 *---------------------------------------------------------------------------
 */
CleanUp()
{
	close(sock);
	Log("Bed process exiting\n");
}



/* 
 * obtainlock.c - Routines for obtaining a lock on a remote machine
 * 
 * Author:	Jim Griffioen
 * 		Dept. of Computer Sciences
 * 		Purdue University
 * Date:	Tue May 24 22:10:01 1988
 *
 * Copyright (c) 1988 Jim Griffioen
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <setjmp.h>
#include <errno.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <string.h>

#include "../h/utils.h"
#include "../h/bed.h"
#include "../h/bmutils.h"
#include "../h/netutils.h"
#include "../h/status.h"


extern char *getlogin();	/* system routine to get login id	*/
jmp_buf env;			/* used to return from read time-outs	*/
int errno;		        /* error number when system err		*/

/*----------------------------------------------------------------------
 * reqlock - request lock on remote machine 
 *----------------------------------------------------------------------
 */
reqlock(fename, bename)
char *fename;				/* name of frontend with bename	*/
char *bename;				/* name of backend desired	*/
{
	int i;
	struct bm bm;
	struct lockreq *lreq;
	char *sb;
	char buf[MAXMACHINENAME];
	int sock;

	

					/* make lock request packet	*/
	bm.ver = CURVER;
	sprintf(bm.cmd, "%d", REQ_LOCK);
	lreq = (struct lockreq *) bm.detail;
	sb = getlogin();
	strcpy(lreq->uid, sb);
	if (gethostname(buf, MAXMACHINENAME) != 0) {
		strcpy(buf, "dunno");
		fprintf(stderr, "error getting local host name\n");
	}
	strcpy(lreq->hostid, buf);
	strcpy(lreq->bename, bename);

	
	sock = ConnectUdp (fename, KNOWN_UDP_PORT);

	if (bmsend (sock, &bm, lbm, 0) <= 0)
	    SysError ("send");

	bmrecv (sock, &bm, lbm, 0);

	if (atoi(bm.cmd) != RESP_OK)
	    return(SYSERR);
	else
	    return(SYSOK);
}


/*---------------------------------------------------------------------------
 * obtainlock - Obtains and locks a machine, or verifies a current lock
 *		- if bename != "" then we try for bename
 *		- else we try for anything in class
 *---------------------------------------------------------------------------
 */
obtainlock(class, fename, bename, unspecifiedclass)
char *class;				/* class machine desired	*/
char *fename;				/* front end to use (out param)	*/
char *bename;				/* backend to use (in/out param)*/
char unspecifiedclass;			/* user did not specify class	*/
{
	FILE *fs;			/* lock file ptr		*/
	char filename[256];		/* temp filename variable	*/
	struct stat statbuf;		/* status of file struct	*/
	char femachine[MAXMACHINENAME];	/* temp fename str variable	*/
	char bemachine[MAXMACHINENAME];	/* temp bename str variable	*/
	char beclass[CLASSLEN];		/* temp class str variable	*/
	int i, j;			/* counter variable		*/
	struct bm *bm[30];		/* list of status messages	*/
	struct statresp *stresp;	/* temp status response ptr	*/
	struct bestatus *bestat;	/* temp backend status ptr	*/
	int nummach;			/* number of machines		*/
	int minutes;			/* number of minutes idle	*/
	

	

	checkbasedir();
	
	strcpy(filename, BASEDIR);
	strcat(filename, getlogin());
	
	if (stat(filename, &statbuf) == 0) { /* lock file exists */
		/* user has mach reserved - try it */
		fs = fopen(filename, "r");
		fscanf(fs, "%s %s %s", femachine, bemachine, beclass);
		fclose(fs);
		if ((strcmp(class, beclass) == 0) ||
		    (unspecifiedclass)) { 	/* it is the same class? */
			if ((strlen(bename) == 0) || /* is it the same mach? */
			    (strcmp(bename,bemachine) == 0)) {
				if (reqlock(femachine, bemachine) == SYSOK) {
					strcpy(fename, femachine);
					strcpy(bename, bemachine);
					return(SYSOK);
				}
			}
			else {		/* release old lock */
				if (releaselock(beclass,bemachine,TRUE)==SYSOK)
				    printf("released lock on machine '%s'\n",bemachine);
				/* fall through and find a new machine */
			}
		}
		else {			/* release old lock */
			if (releaselock(beclass, bemachine, TRUE) == SYSOK)
			    printf("released lock on machine '%s'\n",bemachine);
			/* fall through and find a new machine */
		}
	}


	/* If we get to this point we need to find a free machine 	*/
	/* First check if the user has one reserved, but we did not 	*/
	/* know about it cause there was no local lock file		*/
	nummach = obtainstatus(bm);	/* get status from all machines	*/
	for (i = 0; i < nummach; i++) {
		stresp = (struct statresp *) bm[i]->detail;
		for (j = 0; j < atoi(stresp->festatus.numbends); j++) {
			bestat = &(stresp->bestatus[j]);
			if ((strcmp(class, bestat->class) == 0) &&
			    (strlen(bename) == 0) &&
			    (strcmp(getlogin(), bestat->user) == 0)) {
				if (reqlock(stresp->festatus.fename,
					    bestat->bename) == SYSOK) {
					strcpy(fename,stresp->festatus.fename);
					strcpy(bename,bestat->bename);
					fs = fopen(filename, "w+");
					fprintf(fs, "%s %s %s", fename,bename,
						class);
					fclose(fs);
					return(SYSOK);
				}
				/* else keep looking */
			}
		}
	}

	/* if we get here, just grap the first free machine 	*/
	for (i = 0; i < nummach; i++) {
		stresp = (struct statresp *) bm[i]->detail;
		for (j = 0; j < atoi(stresp->festatus.numbends); j++) {
			bestat = &(stresp->bestatus[j]);
			minutes = getidleminutes(bestat->idle);
			if ((strcmp(class, bestat->class) == 0) &&
			    ((strlen(bename) == 0) ||
			     (strcmp(bename, bestat->bename) == 0)) &&
			    ((minutes >= RESERVETIME) || 
			    (strcmp(NOBODY, bestat->user) == 0))) {
				if (strcmp(NOBODY, bestat->user) != 0) {
					/* idle time exceeded */
					releaselock(bestat->class,
						    bestat->bename,
						    FALSE);
				}
				if (reqlock(stresp->festatus.fename,
					    bestat->bename) == SYSOK) {
					strcpy(fename,stresp->festatus.fename);
					strcpy(bename,bestat->bename);
					fs = fopen(filename, "w+");
					fprintf(fs, "%s %s %s", fename,bename,
						class);
					fclose(fs);
					return(SYSOK);
				}
				/* else keep looking */
			}
		}
	}
	return(SYSERR);
}


/*---------------------------------------------------------------------------
 * getidleminutes - extract minutes from idletime string
 *---------------------------------------------------------------------------
 */
getidleminutes(idletime)
char *idletime;
{
	int hours, minutes, seconds;

	sscanf(idletime, "%d:%d:%d", &hours, &minutes, &seconds);
	return(minutes);
}


/*---------------------------------------------------------------------------
 * checkbasedir - make sure that BASEDIR is there
 *---------------------------------------------------------------------------
 */
checkbasedir()
{
	char directory[256];

	/* make sure all the necessary directories and files are there */
	strcpy(directory, BASEDIR);
	directory[strlen(directory)-1] = '\0';	/* remove the backslash */
	if (access(directory, F_OK) != 0) {
		if (mkdir(directory, 0777) != 0) {
			fprintf("directory '%s' not found\n", directory);
			exit(1);
		}
	}
}

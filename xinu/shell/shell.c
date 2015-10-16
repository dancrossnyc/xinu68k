#include <stddef.h>
#include <string.h>

#include "conf.h"
#include "kernel.h"
#include "mem.h"
#include "proc.h"
#include "shell.h"
#include "cmd.h"
#include "tty.h"

struct shvars Shl;		// globals used by Xinu shell
struct cmdent cmds[] = {	// shell commands
	{"bpool",	FALSE,		x_bpool},
	{"cat",		FALSE,		x_cat},
	{"close",	FALSE,		x_close},
	{"cp",		FALSE,		x_cp},
	{"create",	FALSE,		x_creat},
	{"date",	FALSE,		x_date},
	{"devs",	FALSE,		x_devs},
	{"dg",		FALSE,		x_dg},
	{"echo",	FALSE,		x_echo},
	{"exit",	TRUE,		x_exit},
	{"help",	FALSE,		x_help},
	{"kill",	TRUE,		x_kill},
	{"logout",	TRUE,		x_exit},
	{"mem",		FALSE,		x_mem},
	{"mount",	FALSE,		x_mount},
	{"mv",		FALSE,		x_mv},
	{"netstat",	FALSE,		x_net},
	{"ps",		FALSE,		x_ps},
	{"reboot",	TRUE,		x_reboot},
	{"rf",		FALSE,		x_rf},
	{"rls",		FALSE,		x_rls},
	{"rm",		FALSE,		x_rm},
	{"routes",	FALSE,		x_routes},
	{"ruptime",	FALSE,		x_uptime},
	{"sleep",	FALSE,		x_sleep},
	{"snap",	FALSE,		x_snap},
	{"time",	FALSE,		x_date},
	{"unmount",	FALSE,		x_unmou},
	{"uptime",	FALSE,		x_uptime},
	{"who",		FALSE,		x_who},
	{"?",		FALSE,		x_help}
};

static char errhd[] = "Syntax error\n";	// global error messages
static char fmt[] = "Cannot open %s\n";
static char fmt2[] = "[%d]\n";

//------------------------------------------------------------------------
// shell - Xinu shell with file redirection and background processing
//------------------------------------------------------------------------
int
shell(int dev)
{
	int ntokens;
	int i, j, k, n;
	size_t len;
	char *outnam, *innam;
	int stdin, stdout, stderr;
	Bool backgnd;
	char ch, hostname[SHMLEN];
	int child;

	Shl.shncmds = sizeof(cmds) / sizeof(struct cmdent);
	getname(hostname, SHMLEN);
	for (;;) {
		fprintf(dev, "%s %% ", hostname);
		getutime(&Shl.shlast);
		if ((n = read(dev, Shl.shbuf, SHBUFLEN)) == 0)
			n = read(dev, Shl.shbuf, SHBUFLEN);
		if (n == EOF)
			break;
		Shl.shbuf[n - 1] = NULLCH;
		if ((ntokens = lexan(Shl.shbuf)) == SYSERR) {
			fprintf(dev, errhd);
			continue;
		}
		if (ntokens == 0)
			continue;
		outnam = innam = NULL;
		backgnd = FALSE;

		// handle '&'
		if (Shl.shtktyp[ntokens - 1] == '&') {
			ntokens--;
			backgnd = TRUE;
		}

		// scan tokens, accumulating length;  handling redirect
		for (len = 0, i = 0; i < ntokens;) {
			if ((ch = Shl.shtktyp[i]) == '&') {
				ntokens = -1;
				break;
			} else if (ch == '>') {
				if (outnam != NULL || i >= --ntokens) {
					ntokens = -1;
					break;
				}
				outnam = Shl.shtok[i + 1];
				for (ntokens--, j = i; j < ntokens; j++) {
					Shl.shtktyp[j] =
					    Shl.shtktyp[j + 2];
					Shl.shtok[j] = Shl.shtok[j + 2];
				}
				continue;
			} else if (ch == '<') {
				if (innam != NULL || i >= --ntokens) {
					ntokens = -1;
					break;
				}
				innam = Shl.shtok[i + 1];
				for (ntokens--, j = i; j < ntokens; j++) {
					Shl.shtktyp[j] =
					    Shl.shtktyp[j + 2];
					Shl.shtok[j] = Shl.shtok[j + 2];
				}
				continue;
			}
			len += strlen(Shl.shtok[i++]) + 1;
		}
		if (ntokens <= 0) {
			fprintf(dev, errhd);
			continue;
		}
		stdin = stdout = stderr = dev;

		// Look up command in table
		for (k = 0; k < Shl.shncmds; k++) {
			if (strcmp(cmds[k].cmdnam, Shl.shtok[0]) == 0)
				break;
		}
		if (k >= Shl.shncmds) {
			fprintf(dev, "%s: not found\n", Shl.shtok[0]);
			continue;
		}

		// handle built-in commands with procedure call
		if (cmds[k].cbuiltin) {
			if (innam != NULL || outnam != NULL || backgnd) {
				fprintf(dev, errhd);
				continue;
			}
			if ((*cmds[k].cproc)(stdin, stdout,
					       stderr, ntokens,
					       Shl.shtok) == SHEXIT)
				break;
			continue;
		}

		// Open files and redirect I/O if specified
		if (innam != NULL &&
		    (stdin = open(NAMESPACE, innam, "ro")) == SYSERR) {
			fprintf(dev, fmt, innam);
			continue;
		}
		if (outnam != NULL &&
		    (stdout = open(NAMESPACE, outnam, "w")) == SYSERR) {
			fprintf(dev, fmt, outnam);
			continue;
		}

		// compute space needed for string arg pointers (in bytes)
		len += (ntokens + 2) * sizeof(char *);
		control(dev, TCINT, getpid());

		// create process to execute conventional command
		// This is terrible; we walk the stack of the calling
		// proc "copying" arguments that just don't exist.
		// Who is to say we won't walk past the top of our own stack?
		// The 3 should be a 4, too.  This should be rewritten.
		if ((child = create(cmds[k].cproc, SHCMDSTK, SHCMDPRI,
				    Shl.shtok[0], 5,
				    stdin, stdout, stderr, ntokens, NULL)) == SYSERR) {
			fprintf(dev, "Cannot create\n");
			close(stdout);
			close(stdin);
			continue;
		}
		addarg(child, ntokens, len);
		setdev(child, stdin, stdout);
		if (backgnd) {
			fprintf(dev, fmt2, child);
			resume(child);
		} else {
			setnok(getpid(), child);
			recvclr();
			resume(child);
			if (receive() == INTRMSG) {
				setnok(BADPID, child);
				fprintf(dev, fmt2, child);
			}
		}
	}

	return OK;
}

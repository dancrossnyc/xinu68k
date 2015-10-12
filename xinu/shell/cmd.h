// Declarations for all commands known by the shell
struct	cmdent	{			// entry in command table
	char	*cmdnam;		// name of command
	Bool	cbuiltin;		// Is this a builtin command?
	int	(*cproc)(int, int, int, int, char *[]);		// procedure that implements cmd
};

extern	int
	x_bpool(),	x_cat(),	x_close(),	x_cp(),
	x_creat(),	x_date(),	x_devs(),	x_dg(),
	x_echo(),	x_exit(),	x_help(),	x_kill(),
	x_mem(),	x_mount(),	x_mv(),		x_net(),
	x_ps(),		x_reboot(),	x_rf(),		x_rls(),
	x_rm(),		x_routes(),	x_sleep(),	x_snap(),
	x_unmou(),	x_uptime(),	x_who();

extern	struct	cmdent	cmds[];

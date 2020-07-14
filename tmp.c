void					ft_start_termcaps(void)
{
	struct termios	term;
	char			*env;

	env = get_variable("TERM");
	if (!env || tgetent(NULL, env) == ERR ||
		tcgetattr(0, &term) == -1)
	{
		free(env);
		ft_dprintf(2, "%s: I need a variable \"TERM\"\n", SHNAME);
		exit(-1);
	}
	ft_memcpy(get_term_save(), &term, sizeof(struct termios));
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
	{
		free(env);
		ft_dprintf(2, "%s: Termcap is lost\n", SHNAME);
		exit(-1);
	}
	free(env);
}

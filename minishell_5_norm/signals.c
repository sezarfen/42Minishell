#include "minishell.h"

void	default_sigint(int sig)
{
	(void)sig;
	g_exitstatus = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	default_sigquit(int sig)
{
	(void)sig;
	printf("\b\b  \b\b");
}

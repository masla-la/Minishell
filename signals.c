#include "minishell.h"

void	sig_child(int sig)
{
	if (sig == SIGINT)
		exit(0);
}

void	sig_rl(int sig)
{
	if (sig == SIGQUIT)
	{
		g_sig = 1;
		write(1, "\n", 1);
		exit(g_sig);
	}
}

void	ft_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
#include "minishell.h"

void	sig_child(int sig)
{
	if (sig == SIGINT || sig == SIGIOT)
	{
		close(WRITE);
		exit(1);
	}
}

void	sig_rl(int sig)
{
	if (sig == SIGIOT)
	{
		g_sig = 1;
		write(1, "\n", 1);
		exit(1);
	}
}

void	ft_sig2(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
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
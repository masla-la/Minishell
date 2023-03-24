#include "minishell.h"

void	sig_child(int sig)
{
	if (sig == SIGINT || sig == SIGIOT)
	{
		close(WRITE);
		exit(1);
	}
}

int	sig_rl(char	*c, t_mini *mini)
{
	free(c);
	ft_free_exprt(mini->exprt);
	g_sig = 1;
	rl_replace_line("exit", 0);
	print_pepe("PrintPepe/pepe2");
	printf("\x1b[31mMinishell:\x1b[0m exit\n");
	return (1);
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

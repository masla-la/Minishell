#include "minishell.h"

int	write_error(t_mini *mini, int err, char *str)
{
	ft_putstr_fd(str, 2);
	ft_exit_error(mini, err);
	return (1);
}
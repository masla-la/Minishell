#include "minishell.h"

int	write_error(t_mini *mini, int err, char *str,char *str2)
{
	ft_putstr_fd(str, 2);
	if (str2)
		ft_putstr_fd(str2, 2);
	ft_putstr_fd("\n", 2);
	ft_exit_error(mini, err);
	return (err);
}
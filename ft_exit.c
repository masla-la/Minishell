#include "minishell.h"

int	ft_isnum(const char *str)
{
	while (*str && *str < 30 && *str > 39)
	{
		if (*str == '=')
			return (0);
		str++;
	}
	return (1);
}

int	ft_check_export(t_mini *mini, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (ft_exit_error(mini, 1));
}

int	ft_add_to_env(t_mini *mini, char *str)
{
	t_exprt	*exprt;

	exprt = mini->exprt;
	if (ft_isnum(str))
		return (ft_exit_error(mini, 1));
	while (exprt)
	{
		if (strncmp(str, exprt->env, ft_check_export(mini, str)))
		{
			free(exprt->env);
			exprt->env = ft_strdup(str);
			return (0);
		}
		exprt = exprt->next;
	}
	ft_lstadd_exp(&exprt, ft_lstnew_exp(NULL));
	exprt = exprt->next;
	exprt->env =	ft_strdup(str);
	return (0);
}

int	ft_exit_error(t_mini *mini, int	error)
{
	char	*dest;
	char	*er;

	er = ft_itoa(error);
	dest = ft_strjoin("$?=", er);
	ft_free(mini);
	ft_add_to_env(mini, dest);
	free(dest);
	return (error);
}
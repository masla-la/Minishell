#include "minishell.h"

int	ft_isnum(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] < '0' || str[i] > '9'))
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	if (!str[i])
		return (0);
	return (EXIT_FAILURE);
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

	if (!str && ft_isnum(str))
		return (ft_exit_error(mini, 1));
	exprt = mini->exprt;
	while (exprt->env)
	{
		if (!strncmp(str, exprt->env, ft_check_export(mini, str)))
		{
			free(exprt->env);
			exprt->env = ft_strdup(str);
			return (0);
		}
		exprt = exprt->next;
	}
	ft_lstadd_exp(&exprt, ft_lstnew_exp(NULL));
	exprt->env = ft_strdup(str);
	return (0);
}//se pierden los datos

int	ft_exit_error(t_mini *mini, int	error)
{
	char	*dest;
	char	*er;

	er = ft_itoa(error);
	dest = ft_strjoin("?=", er);
	ft_free(mini);
	ft_add_to_env(mini, dest);
	free(dest);
	return (error);
}
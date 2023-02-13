#include "minishell.h"

t_exprt	*ft_lstnew_exp(void *content)
{
	t_exprt *rtn;

	rtn = (t_exprt *)malloc(sizeof(t_exprt));
	if (!rtn)
		return (NULL);
	rtn->next = NULL;
	rtn->env = content;
	return (rtn);
}

t_exprt	*ft_lstlast_exp(t_exprt *exprt)
{
	if (!exprt)
		return (NULL);
	while (exprt)
	{
		if (exprt->next == NULL)
			return (exprt);
		exprt = exprt->next;
	}
	return (exprt);
}

void	ft_lstadd_exp(t_exprt **exprt, t_exprt *new)
{
	if (!*exprt)
		*exprt = new;
	else
		ft_lstlast_exp(*exprt)->next = new;
}

char	*ft_find_env(t_mini *mini, char *str)
{
	t_exprt *exprt;

	exprt = mini->exprt;
	while (ft_strncmp(str, exprt->env, ft_strlen(str)))
	{
		exprt = exprt->next;
		if (!exprt->next)
			return (NULL);
	}
	return (ft_strdup(exprt->env + ft_strlen(str) + 1));
}

int		ft_get_env(t_mini *mini, char **env)
{
	int		i;
	t_exprt	*exprt;

	i = 0;
	exprt = (t_exprt *)malloc(sizeof(t_exprt));
	mini->exprt = exprt;
	exprt->next = NULL;
	if (!mini->exprt)
		return (EXIT_FAILURE);
	while (*env)
	{
		exprt->env = ft_strdup(*env);
		ft_lstadd_exp(&exprt, ft_lstnew_exp(NULL));
		exprt = exprt->next;
		env++;
	}
	exprt->env = ft_strdup("?=0");
	return (0);
}

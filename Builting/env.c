#include "../minishell.h"

int	ft_rm_to_env(t_mini *mini, char *str)
{
	t_exprt	*exprt;
	t_exprt	*aux;
	t_exprt	*tmp;

	exprt = mini->exprt;
	aux = NULL;
	tmp = NULL;
	while(strncmp(exprt->env, str, ft_strlen(str)))
	{
		aux = exprt;
		exprt = exprt->next;
	}
	if (!strncmp(exprt->env, str, ft_strlen(str)))
	{
		if (exprt->next != NULL)
			tmp = exprt->next;
		free(exprt->env);
		free(exprt);
		if (aux != NULL)
			exprt = aux;
		if (tmp != NULL)
			exprt->next = tmp;
	}
	return (EXIT_SUCCESS);
}

int	ft_print_env(t_mini *mini)
{
	t_exprt	*exprt;

	exprt = mini->exprt;
	while(exprt->env)
	{
		printf("%s\n", exprt->env);
		exprt = exprt->next;
	}
	return (EXIT_SUCCESS);
}
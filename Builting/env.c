#include "../minishell.h"

int	ft_rm_to_env(t_mini *mini, char *str)
{
	t_exprt	*exprt;
	t_exprt	*aux;

	exprt = mini->exprt;
	aux = NULL;
	while(!strncmp(exprt->env, str, ft_strlen(str)))
	{
		aux = exprt;
		exprt = exprt->next;
	}
	if (strncmp(exprt->env, str, ft_strlen(str)))
	{
		aux->next = exprt->next;
		free(exprt->env);
		free(exprt);
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
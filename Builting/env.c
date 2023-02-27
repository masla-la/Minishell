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

void	print_export(char **export)
{
	int	i;
	int	n;

	n = 0;
	while (export[n])
	{
		i = 0;
		printf("declare -x ");
		while(export[n][i])
		{
			printf("%c", export[n][i]);
			if (export[n][i] == '=')
				printf("%c", 39);
			i++;
		}
		printf("%c\n", 39);
		n++;
	}
}

//FT especifica del comando export sin argumentos
int	order_env(t_mini *s)
{
	int		i[2];
	char	**env_cpy;
	char	*tmp = NULL;

	env_cpy = ft_doublestrdup((*s).env);
	i[0] = 0;
	while (env_cpy[i[0] + 1])
	{
		i[1] = i[0] + 1;
		while (i[1] < ft_doublestrlen(s->env))
		{
			if (ft_strcmp(env_cpy[i[0]], env_cpy[i[1]]) > 0)
			{
				tmp = ft_strdup(env_cpy[i[0]]);
				env_cpy[i[0]] = ft_strdup(env_cpy[i[1]]);
				env_cpy[i[1]] = ft_strdup(tmp);
				free(tmp);
			}
			i[1]++;
		}
		i[0]++;
	}
	print_export(env_cpy);
	ft_doublefree(env_cpy);
	return (1);
}

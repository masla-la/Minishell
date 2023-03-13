/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamorr <jchamorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:00:12 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/13 19:01:40 by jchamorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_rm_to_env(t_mini *mini, char *str)
{
	t_exprt	*exprt;
	t_exprt	*aux;
	t_exprt	*tmp;

	exprt = mini->exprt;
	aux = NULL;
	tmp = NULL;
	while (strncmp(exprt->env, str, ft_strlen(str)))
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
	while (exprt->env)
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
		while (export[n][i])
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

char	**ft_lst_to_doublestr(t_exprt *s)
{
	t_exprt		*len;
	char		**env_cpy;
	int			i;

	len = s;
	i = 0;
	while (len->next)
	{
		len = len->next;
		i++;
	}
	len = s;
	env_cpy = malloc(sizeof(char *) * (i + 1));
	if (!env_cpy)
		return (NULL);
	i = 0;
	while (len->next)
	{
		env_cpy[i] = ft_strdup(len->env);
		len = len->next;
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

//FT especifica del comando export sin argumentos
int	order_env(t_mini *s)
{
	int		i;
	int		j;
	char	**env_cpy;
	char	*tmp;

	env_cpy = ft_lst_to_doublestr(s->exprt);
	i = 0;
	while (env_cpy[i + 1])
	{
		j = i + 1;
		while (j < ft_doublestrlen(env_cpy))
		{
			if (ft_strcmp(env_cpy[i], env_cpy[j]) > 0)
			{
				tmp = env_cpy[i];
				env_cpy[i] = env_cpy[j];
				env_cpy[j] = tmp;
			}
			j++;
		}
		i++;
	}
	print_export(env_cpy);
	ft_doublefree(env_cpy);
	return (1);
}

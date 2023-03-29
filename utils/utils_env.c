/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamorr <jchamorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:24:28 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/29 14:16:03 by jchamorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exprt	*ft_lstnew_exp(void *content)
{
	t_exprt	*rtn;

	rtn = malloc(sizeof(t_exprt));
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
	t_exprt	*exprt;
	char	*str_2;

	exprt = mini->exprt;
	while (exprt->env && ft_strncmp(str, exprt->env, ft_strlen(str)))
	{
		exprt = exprt->next;
		if (!exprt->next)
			return (NULL);
	}
	str_2 = ft_strjoin2(str, "=");
	if (!ft_strncmp(str_2, exprt->env, ft_strlen(str_2)) || \
		exprt->env[ft_strlen(str_2)] == '\0')
	{
		free (str_2);
		return (ft_strdup(exprt->env + ft_strlen(str) + 1));
	}
	return (NULL);
}

int	ft_get_env(t_mini *mini, char **env)
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
	ft_add_to_env(mini, "?=0");
	return (0);
}

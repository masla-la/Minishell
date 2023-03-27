/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masla-la <masla-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:36:58 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/27 11:51:45 by masla-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	check_add(char *str, char *env)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (env[i] && env[i] != '=')
		i++;
	while (n < i && env[n] == str[n])
		n++;
	if (env[n] != str[n])
		return (0);
	return (1);
}

int	ft_add_to_env(t_mini *mini, char *str)
{
	t_exprt	*exprt;

	if (!str || ft_isnum(str))
	{
		printf("export: not an identifier: %s\n", str);
		return (ft_exit_error(mini, 1));
	}
	exprt = mini->exprt;
	if (!ft_check_export(mini, str))
		return (1);
	while (exprt->env)
	{
		if (check_add(str, exprt->env))
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
}

int	ft_exit_error(t_mini *mini, int error)
{
	char	*dest;
	char	*er;

	er = ft_itoa(error);
	dest = ft_strjoin2("?=", er);
	ft_add_to_env(mini, dest);
	free(dest);
	return (error);
}
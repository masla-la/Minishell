/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamorr <jchamorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:43:43 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/29 15:43:44 by jchamorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quote_to_expand(int quote, char *arg, int i)
{
	if (arg[i] == 39 && quote == 0)
		return (1);
	else if (arg[i] == 39 && quote == 1)
		return (0);
	return (quote);
}

int	check_dl(char *str, int i)
{
	int	n;

	n = i;
	while (str[n] && str[n] != ' ' && str[n] != ':'\
	&& str[n] != ';' && str[n] != '$' && str[n] != '\0')
		n++;
	if (n - 1 <= i)
		return (0);
	return (1);
}

char	*ft_expand(char *arg, t_mini *mini)
{
	int		i;
	char	*arg_cpy;
	int		quote;

	i = -1;
	quote = 0;
	arg_cpy = ft_strdup2(arg);
	while (arg[++i])
	{
		quote = check_quote_to_expand(quote, arg, i);
		if (arg[i] == '$' && arg[i + 1] && quote == 0)
			if (check_dl(arg, i + 1))
				return (ft_expand_var(mini, arg, arg_cpy, i));
	}
	free(arg);
	return (arg_cpy);
}

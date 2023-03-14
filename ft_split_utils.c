/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamorr <jchamorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:31:54 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/14 18:03:53 by jchamorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_condition(char **dst, int *i, char *s, char c)
{
	dst[i[1]][i[2]] = '\0';
	i[2] = 0;
	i[0]++;
	i[1]++;
	dst[i[1]] = (char *)malloc(sizeof(char) * ft_cmd_len(s, i[0], c));
	if (!dst[i[1]])
		exit (1);
	return (dst);
}

int	split_condition_quote(char **dst, int *i, char *s, char quote)
{
	dst[i[1]][i[2]] = '\0';
	i[1]++;
	dst[i[1]] = malloc(sizeof(char) * (ft_cmd_len(s, i[0], quote) + 2));
	if (!dst[i[1]])
		exit (1);
	return (0);
}

int	split_condition_2(int in_quotes, char *type, char c)
{
	*type = c;
	return (1);
}

int	another_condition(char *s, int *i, int in_quotes, char **dst)
{
	if (s[i[0]] != 32 || in_quotes)
	{
		dst[i[1]][i[2]] = s[i[0]];
		return (1);
	}
	return (0);
}

void	final_split_condition(int *i, char **dst)
{
	if (i[2] > 0)
	{
		dst[i[1]][i[2]] = '\0';
		//printf("I de 1 de 0 %c\n", dst[i[1]][0]);
		if (dst[i[1]][0] != '\0')
			i[1]++;
	}
	dst[i[1]] = NULL;
	return ;
}

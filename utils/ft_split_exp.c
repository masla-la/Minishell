/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masla-la <masla-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:38:41 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/30 11:10:45 by masla-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_cpyn(char *s, int start, int end)
{
	int		i;
	int		n;
	char	*dest;

	if (s[start] == 34 || s[start] == 39)
		end++;
	dest = malloc(sizeof(char) * (end - start + 2));
	if (!dest)
		return (NULL);
	i = start;
	n = 0;
	while (s[i] && i < end)
	{
		dest[n] = s[i];
		n++;
		i++;
	}
	dest[n] = '\0';
	return (dest);
}

int	is_quote_closed(char *s)
{
	int	i;
	int	type;
	int	inside;

	i = 0;
	type = 0;
	inside = 0;
	while (s[i])
	{
		if ((s[i] == 34 || s[i] == 39) && inside == 0)
		{
			inside = 1;
			type = s[i];
		}
		else if (s[i] == type && inside == 1)
		{
			inside = 0;
			type = 0;
		}
		i++;
	}
	if (inside == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

char	**ft_fill_2(char **dst, char *s)
{
	int		i[3];
	char	quote_type;

	i[0] = -1;
	i[1] = 0;
	i[2] = 0;
	quote_type = '\0';
	dst = ft_exp(dst, s, quote_type, i);
	return (dst);
}

size_t	ft_lines_2(char *s, char c, int quotes)
{
	size_t	i;

	i = 0;
	while (*s == c && *s != '\0')
		s++;
	i = ft_exp_2(s, quotes, i, c);
	return (i);
}

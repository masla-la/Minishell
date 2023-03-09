/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamorr <jchamorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:38:41 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/08 18:02:50 by jchamorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_ignore_split(char const *s, size_t i)
{
	size_t	n;
	size_t	c;

	n = 0;
	c = 0;
	while (s[i + c] && (s[i] == 34 || s[i] == 39) && n < 2)
	{
		if (s[i + c] == 34 || s[i + c] == 39)
			n++;
		c++;
	}
	if (c != 0)
		return (i + c - 1);
	return (i);
}

size_t	ft_len_exp(char const *s, char c)
{
	size_t	count;
	int		i;

	count = 0;
	i = 0;
	while (*s == c && *s)
		s++;
	while (*s)
	{
		while (*s != c && *s)
		{
			if (*s == 34 || *s == 39)
				i = 1;
			if ((*s == 34 || *s == 39) && i == 1)
				i = 0;
			s++;
		}
		while (*s == c && *s && i == 0)
			s++;
		while (*s && i == 1 && (*s != 34 || *s != 39))
			s++;
		count++;
	}
	return (count);
}

char	*ft_splitt_exp(char const *s, size_t start, size_t finish)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = malloc(sizeof(char) * (finish - start + 1));
	if (!dest)
		return (NULL);
	while (start < finish)
		dest[i++] = s[start++];
	dest[i] = '\0';
	return (dest);
}

char	**ft_divider_exp(char **dest, char const *s, char c)
{
	size_t	i;
	size_t	z;
	size_t	n;

	i = 0;
	z = 0;
	n = 0;
	while (s[i])
	{
		while (s[i] != c && s[i])
		{
			i = ft_ignore_split(s, i);
			i++;
			if (s[i] == c || i == ft_strlen(s) || s[i] == 34 || s[i] == 39)
				dest[z++] = ft_splitt_exp(s, n, i);
		}
		while (s[i] == c && s[i])
		{
			i++;
			n = i;
		}
	}
	dest[z] = NULL;
	return (dest);
}

char	**ft_split_exp(char const *s, char c)
{
	char	**dest;

	if (!s)
		return (NULL);
	dest = malloc(sizeof(char *) * (ft_len_exp(s, c) + 1));
	if (!dest)
		return (NULL);
	ft_divider_exp(dest, s, c);
	return (dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masla-la <masla-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:38:41 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/13 12:53:24 by masla-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* size_t	ft_ignore_split(char const *s, size_t i)
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
	int		quotes;

	count = 0;
	i = 0;
	while (*s == c && *s)
		s++;
	while (*s)
	{
		while (*s != c && *s)
		{
			if ((*s == 34 || *s == 39) && i == 0)
			{
				quotes = *s;
				i = 1;
			}
			if ((*s == quotes) && i == 1)
				i = 0;
			s++;
		}
		while (*s == c && *s && i == 0)
			s++;
		while (*s && i == 1 && (*s != quotes))
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
	dest = malloc(sizeof(char *) * (ft_len_exp(s, c) + 2));
	if (!dest)
		return (NULL);
	ft_divider_exp(dest, s, c);
	return (dest);
} */

size_t ft_lines_2(const char* s, char c)
{
	size_t	i = 0;
	int		quotes = 0;

	while (*s == c && *s != '\0')
		s++;
	while (*s != '\0')
	{
		if (*s == 34 || *s == 39)
		{
			if (quotes == 0)
				quotes = *s;
			else if (quotes == *s)
				quotes = 0;
		}
		if (*s == c && quotes == 0)
		{
			i++;
			while (*s == c && *s != '\0')
				s++;
		}
		else
			s++;
	}
	if (quotes != 0) // Hay que poner un error aquí por si las comillas no están cerradas.
		return (i);
	return (i + 1);
}

int	ft_cmd_len(char const *s, int i, char c)
{
	int	n;

	n = 1;
	while (s[i + n] && s[i + n] != c)
		n++;
	printf("%d\n", n + 1);
	return (n + 1);
}

char **ft_fill_2(char **dst, const char *s, char c)
{
	int		i[3];
	int		in_quotes; // flag para indicar si estamos dentro de comillas
	char	quote_type; // comilla doble o simple

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	in_quotes = 0;
	dst[i[1]] = (char *)malloc(sizeof(char) * ft_cmd_len(s, i[0], c));
	while (s[i[0]])
	{
		if (s[i[0]] == c && in_quotes == 0 && s[i[0] + 1] != 34 && s[i[0] + 1] != 39)
		{
			dst[i[1]][i[2]] = '\0';
			i[2] = 0;
			i[0]++;
			i[1]++;
			printf("1-%d\n", ft_cmd_len(s, i[0], c));
			dst[i[1]] = (char *)malloc(sizeof(char) * ft_cmd_len(s, i[0], c));
		}
		if (s[i[0]] == 34 || s[i[0]] == 39)
		{
			if (!in_quotes)
			{
				in_quotes = 1;
				quote_type = s[i[0]];
			}
			else if (quote_type == s[i[0]])
				in_quotes = 0;
			if (in_quotes && s[i[0]] == quote_type)
			{
				dst[i[1]][i[2]] = '\0';
				i[1]++;
				i[2] = 0;
				dst[i[1]] = malloc(sizeof(char) * (ft_cmd_len(s, i[0], quote_type) + 2));//cambiar cmd_len
			}
		}
		if (s[i[0]] != c || in_quotes)
		{
			dst[i[1]][i[2]] = s[i[0]];
			i[2]++;
		}
		i[0]++;
	}
	if (i[2] > 0)
	{
		dst[i[1]][i[2]] = '\0';
		i[1]++;
	}
	dst[i[1]] = NULL;
	return (dst);
}


char	**ft_split_quotes(char const *s, char c)
{
	char	**dst;

	if (!s)
		return (NULL);
	dst = (char **)malloc(sizeof(char *) * (ft_lines_2(s, c) + 1));
	if (!dst)
		return (NULL);
	ft_fill_2(dst, s, c);
	return (dst);
}

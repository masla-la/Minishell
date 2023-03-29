/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamorr <jchamorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:38:41 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/29 19:02:47 by jchamorr         ###   ########.fr       */
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

char	**ft_fill_2(char **dst, char *s, char c)
{
	int		i;
	int		n;
	int		in_quote;
	char	quote_type;

	i = 0;
	n = 0;
	in_quote = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i + 1] && (s[i] == 34 || s[i] == 39))
		{
			in_quote = 1;
			quote_type = s[i];
		}
		if (s[i] != c && in_quote == 0)
		{
			dst[n++] = ft_strdup_space(s, c, i);
			i += ft_strlen(dst[n - 1]) - 1;
		}
		else if (in_quote == 1)
		{
			dst[n++] = ft_strdup_quote(s, i, quote_type);
			in_quote = 0;
			i += ft_strlen(dst[n - 1]) - 1;
		}
		if (s[i] == '\0')
			break ;
		i++;
	}
	dst[n] = NULL;
	return (dst);
}

size_t	ft_lines_2(char *s, char c, int quotes)
{
	size_t	i;

	i = 0;
	while (*s == c && *s != '\0')
		s++;
	while (*s != '\0')
	{
		if (*s == 34 || *s == 39)
		{
			if (quotes == *s && (*(s) == 34 || *(s + 1) == 39))
			{
				i++;
				if (*(s + 1) != '\0' && *(s + 1) != ' ')
					s++;
			}
			if (quotes == 0)
				quotes = *s;
			else if (quotes == *s)
				quotes = 0;
		}
		if (*s == c && quotes == 0 && *(s + 1) && *(s + 1) != 32)
		{
			i++;
			while (*s == c && *s != '\0')
				s++;
		}
		else
			s++;
	}
	return (i + 1);
}

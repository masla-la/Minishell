/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamorr <jchamorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:38:41 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/21 18:04:42 by jchamorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while(s[i] && i < end)
	{
		dest[n] = s[i];
		n++;
		i++;
	}
	dest[n] = '\0';
    //printf("dest->%s\n", dest);
	return (dest);
}
char	*ft_strdup_space(char *s, char c, int start)
{
	int i;

	i = start + 1;
	while(s[i] && s[i] != c && s[i] != 34 && s[i] != 39)
		i++;
	return (ft_cpyn(s, start, i));
}

// La idea es llamar a la ft antes de hacer el split o fill
// Creo que está ready, solo falta llamarla por ahí
int		is_quote_closed(char *s)
{
	int	i;
	int	type;
	int	inside;

	i = 0;
	type = 0;
	inside = 0;
	while(s[i])
	{
		if ((s[i] == 34 || s[i] == 39) && inside == 0)
		{
			inside = 1;
			type = s[i];
			if (s[i + 1])
				i++;
		}
		if (s[i] == type && inside == 1)
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

char	*ft_strdup_quote(char *s, int start, char quote_type)
{
	int i;

	if (start + 1)
		i = start + 1;
	while(s[i] != quote_type)
		i++;
	return (ft_cpyn(s, start, i));
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
	while(s[i])
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
			dst[n] = ft_strdup_space(s, c, i);
			n++;
			i += ft_strlen(dst[n - 1]) - 1;
		}
		else if (in_quote == 1) /*&&  is_quote_closed(s, i, quote_type)) */ // Lo comentado no va a hacer falta
		{
			dst[n] = ft_strdup_quote(s, i, quote_type);
			in_quote = 0;
			n++;
			i += ft_strlen(dst[n - 1]) - 1;
		}
		if (s[i] == '\0')
			break;
		i++;
	}
	dst[n] = NULL;
	return (dst);
}

int	init_vars(int *i, int quotes, char **dst, char *s)
{
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	dst[i[1]] = (char *)malloc(sizeof(char) * ft_cmd_len(s, i[0], 32));
	if (!dst[i[1]])
		exit (1);
	return (0);
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
		if (*s == c && quotes == 0 && *(s + 1) && *(s + 1) != 32)//
		{
			i++;
			while (*s == c && *s != '\0')
				s++;
		}
		else
			s++;
	}
	//printf("Nº ARGS %zu\n", i);
	return (i + 1);
}

int	ft_cmd_len(char *s, int i, char c)
{
	int	n;
	int	z;

	n = 0;
	z = i;
	while (s[z + n])
		n++;
	return (n + 1);
}

/* char	**ft_fill_2(char **dst, char *s, char c)
{
	int		i[3];
	int		in_quotes;
	char	quote_type;

	in_quotes = init_vars(i, in_quotes, dst, s);
	while (s[i[0]])
	{
		if (s[i[0]] == c && in_quotes == 0 && s[i[0] + 1] \
			!= 34 && s[i[0] + 1] != 39)
			{
				if (s[i[0] + 1] == c)
					i[0]++;
				else if (s[i[0] + 1])
					dst = split_condition(dst, i, s, c);
			}
		if (s[i[0]] == 34 || s[i[0]] == 39)
		{
			if (!in_quotes)
				in_quotes = split_condition_2(in_quotes, &quote_type, s[i[0]]);
			else if (quote_type == s[i[0]])// Entra si el primer char son comillas
			{
				dst[i[1]][i[2] + 1] = s[i[0]];
				in_quotes = 0;
				dst[i[1]][i[2]] = s[i[0]];
				printf("El dest[i1] = %c\n",dst[i[1]][i[2]]);
				i[2] += another_condition(s, i, in_quotes, dst);
				printf("El char c = %c\n", c);
				s[i[0]] = c;
				if (s[i[0] - 1] == quote_type)
					i[0]--;
			}
			if (in_quotes && s[i[0]] == quote_type)
				i[2] = split_condition_quote(dst, i, s, quote_type);
		}
		i[2] += another_condition(s, i, in_quotes, dst);
		i[0]++;
	}
	final_split_condition(i, dst);
	return (dst);
} */

char	**ft_split_quotes(char *s, char c)
{
	char	**dst;

	if (!s)
		return (NULL);
	if (is_quote_closed(s))
		return (0);
	dst = (char **)malloc(sizeof(char *) * (ft_lines_2(s, c, 0) + ft_strlen(s)));
	if (!dst)
		return (NULL);
	ft_fill_2(dst, s, c);
	return (dst);
}

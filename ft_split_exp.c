/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamorr <jchamorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:38:41 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/18 19:44:20 by jchamorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**ft_fill_2(char **dst, char *s, char c)
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
			printf("PASO 1\n");
			if (!in_quotes)
				in_quotes = split_condition_2(in_quotes, &quote_type, s[i[0]]);
			else if (quote_type == s[i[0]])// No entiendo ésto.
			{
				printf("PASO 2 -> i = %d\n", i[2]);
				printf("El char i[2] = %c\n", dst[i[1]][i[2]]);
				//dst[i[1]][i[2] + 1] = s[i[0]];
				printf("El char i[2 + 1] = %c\n", dst[i[1]][i[2] + 1]);
				in_quotes = 0;
				dst[i[1]][i[2]] = s[i[0]];
				i[2] += another_condition(s, i, in_quotes, dst);
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
}

char	**ft_split_quotes(char *s, char c)
{
	char	**dst;

	if (!s)
		return (NULL);
	dst = (char **)malloc(sizeof(char *) * (ft_lines_2(s, c, 0) + 1));
	if (!dst)
		return (NULL);
	ft_fill_2(dst, s, c);
	printf("EL COMANDO = %s\n ", dst[1]);
	return (dst);
}

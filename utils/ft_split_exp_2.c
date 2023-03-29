/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_exp_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamorr <jchamorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:57:15 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/29 17:00:03 by jchamorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup_space(char *s, char c, int start)
{
	int	i;

	i = start + 1;
	while (s[i] && s[i] != c && s[i] != 34 && s[i] != 39)
		i++;
	return (ft_cpyn(s, start, i));
}

char	*ft_strdup_quote(char *s, int start, char quote_type)
{
	int	i;

	i = start + 1;
	while (s[i] != quote_type)
		i++;
	return (ft_cpyn(s, start, i));
}

int	init_vars(int *i, char **dst, char *s)
{
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	dst[i[1]] = (char *)malloc(sizeof(char) * ft_cmd_len(s, i[0]));
	if (!dst[i[1]])
		exit (1);
	return (0);
}

int	ft_cmd_len(char *s, int i)
{
	int	n;
	int	z;

	n = 0;
	z = i;
	while (s[z + n])
		n++;
	return (n + 1);
}

char	**ft_split_quotes(char *s, char c)
{
	char	**dst;

	if (!s)
		return (NULL);
	if (is_quote_closed(s))
		return (0);
	dst = (char **)malloc(sizeof(char *) * \
			(ft_lines_2(s, c, 0) + ft_strlen(s)));
	if (!dst)
		return (NULL);
	ft_fill_2(dst, s, c);
	return (dst);
}

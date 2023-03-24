/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masla-la <masla-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:38:33 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/24 10:30:41 by masla-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_cpy_rest(char *arg, char *dest, char *path)
{
	int		i;
	int		n;
	char	*cpy;

	i = -1;
	n = 0;
	while (arg[++i])
	{
		if (arg[i] == '$')
		{
			while (arg[i + n] && arg[i] == '$' && arg[i + n] != ' ')
				n++;
			i += n;
			break ;
		}
	}
	if (!arg[i])
		return (dest);
	cpy = ft_strjoin(dest, arg + i);
	return (cpy);
}

char	*ft_strdup_len(char const *str, int len)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char *) * len + 1);
	while (i < len)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_cpy_var(char *ptr)
{
	char	*var;
	int		i;

	i = 0;
	while (ptr[i] && ptr[i] != ' ')
		i++;
	if (i < 1)
		return (NULL);
	var = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (ptr[i] && ptr[i] != ' ' && ptr[i] != 34)
	{
		var[i] = ptr[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

char	*ft_join_path(char *s1, char *s2)
{
	int		i;
	int		n;
	char	*cpy;
	char	*dest;

	i = 0;
	n = 0;
	cpy = NULL;
	if (!s1 && !s2)
		return (NULL);
	while (s1[i] && s1[i] != '$')
		i++;
	if (!s2 && i == 0)
		return (ft_strdup(""));
	if (i > 0)
		cpy = ft_strdup_len(s1, i);
	if (!cpy)
		return (s2);
	if (!s2)
		return (cpy);
	dest = ft_strjoin(cpy, s2);
	return (dest);
}

char	*ft_expand_var(t_mini *mini, char *arg, char *arg_cpy, int i)
{
	char	*path;
	char	*var;

	var = ft_cpy_var(arg + (i + 1));
	path = ft_find_env(mini, var);
	free(var);
	var = ft_join_path(arg, path);
	var = ft_cpy_rest(arg, var, path);
	if (path && path != var)
		free(path);
	free(arg);
	free(arg_cpy);
	return (ft_expand(var, mini));
}

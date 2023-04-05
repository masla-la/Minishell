/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masla-la <masla-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:15:20 by jchamorr          #+#    #+#             */
/*   Updated: 2023/04/05 09:21:26 by masla-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup2(const char *src)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * (ft_strlen((src)) + i + 100000));
	if (!dest)
		return (NULL);
	if (*src == 39 || *src == 34)
		src++;
	i = 0;
	while (src[i] != 00)
	{
		if (!src[i + 1] && (src[i] == 34 || src[i] == 39))
			break ;
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_init_var(t_mini *mini)
{
	char	*path;

	path = ft_find_env(mini, "PATH");
	mini->path = ft_split(path, ':');
	free(path);
}

int	check_env(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		return (1);
	return (0);
}

int	ft_strcmp2(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s2[i] && s1[i] == s2[i] && ft_strlen(s1) == ft_strlen(s2))
		i++;
	if (i == ft_strlen(s2))
		return (0);
	return (1);
}

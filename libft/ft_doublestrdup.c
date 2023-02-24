/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doublestrdup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamorr <jchamorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:47:09 by jchamorr          #+#    #+#             */
/*   Updated: 2023/02/24 18:56:12 by jchamorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_doublestrdup(char **str)
{
	char	**result;
	int		i;

	if (!str)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (ft_doublestrlen(str) + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		result[i] = ft_strdup(str[i]);
		if (result[i] == NULL)
		{
			ft_doublefree(result);
			errno = ENOMEM;
			return (NULL);
		}
	}
	result[i] = 0;
	return (result);
}
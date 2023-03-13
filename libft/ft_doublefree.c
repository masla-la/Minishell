/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doublefree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamorr <jchamorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:50:26 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/13 19:02:56 by jchamorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_doublefree(char **str)
{
	int	i;

	if (str == NULL)
		return (str);
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
	return (NULL);
}

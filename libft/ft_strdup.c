/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masla-la <masla-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:45:45 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/24 11:24:47 by masla-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;

	if (!s1)
		return (NULL);
	str = malloc(ft_strlen(s1) +1);
	if (!str)
		return (0);
	return (ft_memcpy(str, s1, ft_strlen(s1) + 1));
}

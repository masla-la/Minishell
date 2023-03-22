/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamorr <jchamorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:57:51 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/22 20:48:40 by jchamorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	//write(2, s, ft_strlen(s));
	while (*s != '\0')
	{
		//write(2, "hello\n", 6);
		ft_putchar_fd(*s, fd);
		s++;
	}
}

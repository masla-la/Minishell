/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamorr <jchamorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:00:09 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/13 19:00:10 by jchamorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo_n(t_list *lst)
{
	int	i;

	i = 2;
	while (lst->content[i])
	{
		if (i > 2)
			printf(" ");
		printf("%s", lst->content[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_echo(t_list *lst)
{
	int	i;

	i = 1;
	if (lst->content[i] && !ft_strncmp("-n", lst->content[i], 2))
		return (ft_echo_n(lst));
	while (lst->content[i])
	{
		if (i > 1)
			printf(" ");
		printf("%s", lst->content[i]);
		i++;
	}
	printf("\n");
	return (EXIT_SUCCESS);
}

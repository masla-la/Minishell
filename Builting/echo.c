/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamorr <jchamorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:00:09 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/22 21:02:57 by jchamorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo_n(t_list *lst)
{
	int	i;

	i = 2;
	while (lst->content[i])
	{
		if (i > 1 && lst->content[i] == NULL)
			printf(" ");
		if (lst->content[i])
			printf("%s", lst->content[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_echo(t_list *lst)
{
	int	i;

	i = 1;
	if (lst->content[i] && !ft_strcmp("-n", lst->content[i]))
		return (ft_echo_n(lst));
	while (lst->content[i])
	{
		//ft_putstr_fd(lst->content[i], 2);
		if (i > 1 && lst->content[i] == NULL)
			ft_putstr_fd(" ", 1);
		//write(1, &lst->content[i], 1);
		ft_putstr_fd(lst->content[i], 1);
		i++;
	}
	ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}

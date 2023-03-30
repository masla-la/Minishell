/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masla-la <masla-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:15:29 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/30 12:34:39 by masla-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_wait_childs(t_mini *mini)
{
	t_list	*lst;
	int		i;
	char	*c;
	char	*str_itoa;

	lst = mini->lst;
	while (lst)
	{
		if (lst->pid)
			waitpid(lst->pid, &i, WUNTRACED);
		lst = lst->next;
		WEXITSTATUS(i);
	}
	if (i >= 0)
	{
		str_itoa = ft_itoa(i / 256);
		c = ft_strdup("?=");
		c = ft_strjoin(c, str_itoa);
		if (str_itoa)
			free(str_itoa);
		ft_add_to_env(mini, c);
		free(c);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masla-la <masla-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:38:39 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/10 12:25:23 by masla-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*rtn;

	rtn = malloc(sizeof(t_list));
	if (!rtn)
		return (NULL);
	rtn->next = NULL;
	rtn->content = content;
	return (rtn);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd(t_list **lst, t_list *new)
{
	if (!*lst)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}

int	ft_parse(t_mini *mini, char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		arg[i] = ft_expand(arg[i], mini);
		i++;
	}
	if (arg[0][0] == '|')
		arg++;
	ft_parse_to_lst(mini, arg);
	if (!mini->lst)
		return (EXIT_FAILURE);
	return (EXIT_SUCES);
}

///redirecciones
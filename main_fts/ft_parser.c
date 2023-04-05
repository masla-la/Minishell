/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masla-la <masla-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:38:39 by jchamorr          #+#    #+#             */
/*   Updated: 2023/04/05 11:45:25 by masla-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	int		j;
	t_list	*aux;

	i = 0;
	j = 0;
	ft_parse_to_lst(mini, arg, j);
	aux = mini->lst;
	while (aux)
	{
		i = 0;
		while (aux->content[i])
		{
			aux->content[i] = ft_expand(aux->content[i], mini);
			i++;
		}
		aux = aux->next;
	}
	if (arg[0][0] == '|')
		arg++;
	if (!mini->lst)
		return (EXIT_FAILURE);
	return (EXIT_SUCES);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamorr <jchamorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:38:37 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/18 17:27:28 by jchamorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_comand(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->comand[i])
	{
		//printf("DIR de ARG %p\n", mini->comand[i]);
		if (ft_strlen(mini->comand[i]) > 0)
			free(mini->comand[i]);
		i++;
	}
	free(mini->comand);
	i = 0;
	//printf("ARG QUE LIBERO %s\n", mini->path[i]);
	if (!mini->path)
		return;
	while (mini->path[i])
	{
		free(mini->path[i]);
		i++;
	}
	free(mini->path);
}

void	ft_free_exprt(t_exprt *exprt)
{
	t_exprt	*aux;

	while (exprt)
	{
		aux = exprt->next;
		free(exprt->env);
		free(exprt);
		exprt = aux;
	}
}

void	ft_free_lst(t_list *lst)
{
	int		i;
	t_list	*aux;

	while (lst)
	{
		aux = lst->next;
		i = 0;
		while (lst->content[i])
		{
			free(lst->content[i]);
			i++;
		}
		free(lst->content);
		if (lst->fd[READ])
			close(lst->fd[READ]);
		free(lst);
		lst = aux;
	}
}

void	ft_free(t_mini *mini)
{
	if (mini->lst)
		ft_free_lst(mini->lst);
	if (mini->exprt)
		ft_free_exprt(mini->exprt);
}

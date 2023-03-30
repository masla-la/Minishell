/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamorr <jchamorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:38:37 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/30 20:20:46 by jchamorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_comand(t_mini *mini)
{
	int	i;

	i = 0;
	/* while (mini->comand[i])
	{
		if (ft_strlen(mini->comand[i]) > 0)
			free(mini->comand[i]);
		i++;
	printf("FREE COMAND = %s\n", mini->comand[++i]);
	} */
	free(mini->comand);
	i = 0;
	if (!mini->path)
		return ;
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

	while (exprt->env)
	{
		aux = exprt->next;
		free(exprt->env);
		free(exprt);
		exprt = aux;
	}
	free(exprt);
}

void	ft_free_pepe(t_mini *mini)
{
	int	i;

	i = 0;
	if (!mini->path)
	{
		free(mini->path);
		return ;
	}
	while (mini->path[i])
	{
		free(mini->path[i]);
		i++;
	}
	free(mini->path);
}

void	ft_free_lst(t_list *lst)
{
	int		i;
	t_list	*aux;

	while (lst && lst->next)
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

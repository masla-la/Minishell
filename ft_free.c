#include "minishell.h"

void	ft_free_comand(t_mini *mini)
{
	int	i;

	i = 0;
	while  (mini->comand[i])
	{
		free(mini->comand[i]);
		i++;
	}
	free(mini->comand);
	i = 0;
	while (mini->path[i])
	{
		free(mini->path[i]);
		i++;
	}
	//free(mini->path);
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
	int	i;
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
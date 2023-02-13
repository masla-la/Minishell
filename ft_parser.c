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

int	ft_parse_to_lst(t_mini *mini, char **arg)
{
	int		i;
	t_list	*lst;

	i = 0;
	lst = (t_list *)malloc(sizeof(t_list));
	mini->lst = lst;
	lst->next = NULL;
	lst->content = (char **)malloc(sizeof(char *) * 1);///
	while (arg && *arg)
	{
		if (!ft_strncmp(*arg, "<", 1) || !ft_strncmp(*arg, ">", 1))
			ft_reddir(mini, arg, lst);
		else if (ft_strncmp(*arg, "|", 1))
			lst->content[i++] = ft_strdup(*arg);
		else if (!ft_strncmp(*arg, "|", 1))
		{
			i = 0;
			ft_lstadd(&lst, ft_lstnew(NULL));
			lst = lst->next;
			lst->content = (char **)malloc(sizeof(char *) * 3);
		}
		arg++;
	}
	return (EXIT_SUCES);
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
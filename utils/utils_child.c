#include "../minishell.h"

void	ft_wait_childs(t_mini *mini)
{
	t_list	*lst;

	lst = mini->lst;
	while (lst)
	{
		waitpid(lst->pid, 0, 0);
		lst = lst->next;
	}
}
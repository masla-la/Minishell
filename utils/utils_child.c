#include "../minishell.h"

void	ft_wait_childs(t_mini *mini)
{
	t_list	*lst;
	int		i;

	lst = mini->lst;
	while (lst)
	{
		waitpid(lst->pid, &i, WUNTRACED);
		lst = lst->next;
	}
	WEXITSTATUS(i);
	if (i)
		g_sig = i / 256;
	else
		g_sig = 0;
}
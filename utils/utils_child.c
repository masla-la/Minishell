#include "../minishell.h"

void	ft_wait_childs(t_mini *mini)
{
	t_list	*lst;
	int		i;

	lst = mini->lst;
	while (lst)
	{
		if (lst->pid)
			waitpid(lst->pid, &i, WUNTRACED);
		lst = lst->next;
	}
	WEXITSTATUS(i);
	if (i / 256 == 11)
		g_sig = i / 256;
	else
		g_sig = 0;
}
//falta gestionar los posibles errores para q no den conflicto con el exit o  podemos borrar esta parte
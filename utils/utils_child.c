#include "../minishell.h"

void	ft_wait_childs(t_mini *mini)
{
	t_list	*lst;
	int		i;
	char	*c;

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
		c = ft_strdup("?=");
		c = ft_strjoin(c, ft_itoa(i / 256));
		ft_add_to_env(mini, c);
		free(c);
	}
}
//falta gestionar los posibles errores para q no den conflicto con el exit o  podemos borrar esta parte
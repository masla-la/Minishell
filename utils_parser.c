#include "minishell.h"

int	ft_arg_len(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i][0] != '|')
		i++;
	return (i + 1);
}

int	ft_parse_to_lst(t_mini *mini, char **arg)
{
	int		i;
	t_list	*lst;

	i = 0;
	lst = ft_lstnew(NULL);
	mini->lst = lst;
	lst->content = malloc(sizeof(char *) * ft_arg_len(arg));
	while (arg && *arg)
	{
		if (!ft_strncmp(*arg, "<", 1) || !ft_strncmp(*arg, ">", 1))
			ft_reddir(mini, arg, lst);
		else if (ft_strncmp(*arg, "|", 1))
			lst->content[i++] = ft_strdup(*arg);
		else if (!ft_strncmp(*arg, "|", 1) && (arg + 1) != NULL) //Hace 1 linked de más si encuentra '|' sin más arg
		{
			lst->content[i] = NULL;
			i = 0;
			ft_lstadd_back(&lst, ft_lstnew(NULL));
			lst = lst->next;
			lst->content = malloc(sizeof(char *) * ft_arg_len(arg + 1));
		}
		arg++;
	}
	lst->content[i] = NULL;
	return (EXIT_SUCCESS);
}
//Falta revisar el error de las redirecciones
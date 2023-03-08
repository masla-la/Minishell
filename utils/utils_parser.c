#include "../minishell.h"

int	ft_arg_len(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i][0] != '|')
		i++;
	return (i + 1);
}

int ft_add_something(t_list **linked, int len, int i)
{
    t_list  *new;
    t_list  *copy;
    new = (t_list *)malloc(sizeof(t_list));
    if (!new)
        return (0);
    new->content = malloc(sizeof(char *) * len);
    new->next = NULL;
    copy = (*linked);
    while (copy->next)
        copy = copy->next;
    copy->content[i] = NULL;
    copy->next = new;
    return (0);
}
int ft_parse_to_lst(t_mini *mini, char **arg)
{
    int     i;
    t_list  *lst;
    i = 0;
    lst = ft_lstnew(NULL);
    mini->lst = lst;
    lst->content = malloc(sizeof(char *) * ft_arg_len(arg));
    while (arg && *arg)
    {
        if (!ft_strcmp(*arg, "<") || !ft_strcmp(*arg, ">"))
            ft_reddir(mini, arg, lst);
        else if (ft_strcmp(*arg, "|"))
            lst->content[i++] = ft_strdup(*arg);
        else if (!ft_strcmp(*arg, "|") && (arg + 1)) //Hace 1 linked de más si encuentra '|' sin más arg
        {
            i = ft_add_something(&lst, ft_arg_len(arg + 1), i);
            lst = lst->next;
        }
        arg++;
    }
    lst->content[i] = NULL;
    return (EXIT_SUCCESS);
}
//Falta revisar el error de las redirecciones
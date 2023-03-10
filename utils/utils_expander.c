#include "../minishell.h"

void	ft_reddir_input(t_mini *mini, char *arg, t_list *lst)
{
	lst->input = open(arg, O_RDWR | O_TRUNC | O_CREAT, 0000744);
	if (!access(arg, F_OK))
		ft_exit_error(mini, '1');//acceso al archivo
}

void	ft_reddir_output(t_mini *mini, char *arg, t_list *lst)
{
	lst->output = open(arg, O_RDWR | O_TRUNC | O_CREAT, 0000744);
	if (!access(arg, F_OK))
		ft_exit_error(mini, '1');//acceso al archivo

}

void	ft_reddir_input_2(t_mini *mini, char *arg, t_list *lst)//
{
	lst->input = open(arg, O_RDWR | O_TRUNC | O_CREAT, 0000744);
	if (!access(arg, F_OK))
		ft_exit_error(mini, '1');//acceso al archivo
}

void	ft_reddir_output_2(t_mini *mini, char *arg, t_list *lst)//
{
	lst->output = open(arg, O_RDWR | O_TRUNC | O_CREAT, 0000744);
	if (!access(arg, F_OK))
		ft_exit_error(mini, '1');//acceso al archivo
}

void	ft_reddir(t_mini *mini, char **arg, t_list *lst)
{
	if (!ft_strcmp(*arg, "<"))
		ft_reddir_input(mini, *(arg + 1), lst);
	else if (!ft_strcmp(*arg, ">"))
		ft_reddir_output(mini, *(arg +1), lst);
	else if  (!ft_strcmp(*arg, "<<"))
		ft_reddir_input_2(mini, ++*arg, lst);
	else if (!ft_strcmp(*arg, ">>"))
		ft_reddir_output_2(mini, ++*arg, lst);
	arg++;
}
/////revisar
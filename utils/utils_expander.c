/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masla-la <masla-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:42:28 by jchamorr          #+#    #+#             */
/*   Updated: 2023/04/05 12:42:52 by masla-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_reddir_input(t_mini *mini, char *arg, t_list *lst)
{
	if (lst->input)
		close(lst->input);
	lst->input = open(arg, O_RDONLY);
	if (access(arg, F_OK))
	{
		write(2, "Minishell: ", 12);
		write_error(mini, 1, arg, ": No such file or directory");
	}
	else if (access(arg, F_OK) || access(arg, R_OK))
		write_error(mini, 1, "Minishell: permission denied: ", arg);
}

void	ft_reddir_output(t_mini *mini, char *arg, t_list *lst)
{
	if (lst->output)
		close(lst->output);
	lst->output = open(arg, O_RDWR | O_CREAT);
	if (access(arg, W_OK))
		write_error(mini, 1, "Minishell: permission denied: ", arg);
}

void	ft_reddir_input_2(t_mini *mini, char *arg, t_list *lst)
{
	if (lst->input)
		close(lst->input);
	lst->input = open(arg, O_WRONLY | O_APPEND | O_CREAT, 0660);
	lst->index = 2;
	lst->delimiter = ft_strdup(arg);
	here_doc(lst->input, lst->delimiter);
	if (access(arg, W_OK))
		write_error(mini, 1, "Minishell: permission denied: ", arg);
}

void	ft_reddir_output_2(t_mini *mini, char *arg, t_list *lst)
{
	if (lst->output)
		close(lst->output);
	lst->output = open(arg, O_CREAT | O_WRONLY, 0666);
	here_doc2(lst->output, arg);
	if (access(arg, W_OK))
		write_error(mini, 1, "Minishell: permission denied: ", arg);
}

void	ft_reddir(t_mini *mini, char **arg, t_list *lst, int i)
{
	int	n;

	n = i + 1;
	lst->index = 1;
	while (arg[n] && ft_strcmp2(arg[n], "|"))
		n++;
	n--;
	if (!ft_strcmp2(arg[i], "<<"))
		ft_reddir_input_2(mini, arg[n], lst);
	else if (!ft_strcmp2(arg[i], ">>"))
		ft_reddir_output_2(mini, arg[n], lst);
	else if (!ft_strcmp2(arg[i], "<"))
		ft_reddir_input(mini, arg[n], lst);
	else if (!ft_strcmp2(arg[i], ">"))
		ft_reddir_output(mini, arg[n], lst);
	i = n;
}

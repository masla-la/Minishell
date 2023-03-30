/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masla-la <masla-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:42:28 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/30 13:07:35 by masla-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_reddir_input(t_mini *mini, char *arg, t_list *lst)
{
	lst->input = open(arg, O_RDONLY);
	if (!access(arg, F_OK))
		ft_exit_error(mini, '1');
}

void	ft_reddir_output(t_mini *mini, char *arg, t_list *lst)
{
	lst->output = open(arg, O_RDWR | O_TRUNC | O_CREAT, 0000744);
	if (!access(arg, F_OK))
		ft_exit_error(mini, '1');
}

void	ft_reddir_input_2(t_mini *mini, char *arg, t_list *lst)
{
	lst->input = open(arg, O_RDONLY);
	if (!access(arg, F_OK))
		ft_exit_error(mini, '1');
}

void	ft_reddir_output_2(t_mini *mini, char *arg, t_list *lst)
{
	printf("123\n");
	lst->output = open(arg, O_RDWR | O_TRUNC | O_CREAT, 0000744);
	if (!access(arg, F_OK))
		ft_exit_error(mini, '1');
}

void	ft_reddir(t_mini *mini, char **arg, t_list *lst)
{
	printf("123\n");
	lst->index = 1;
	if (!ft_strcmp(*arg, "<<"))
		ft_reddir_input_2(mini, ++*arg, lst);
	else if (!ft_strcmp(*arg, ">>"))
		ft_reddir_output_2(mini, ++*arg, lst);
	else if (!ft_strcmp(*arg, "<"))
		ft_reddir_input(mini, *(arg + 1), lst);
	else if (!ft_strcmp(*arg, ">"))
		ft_reddir_output(mini, *(arg +1), lst);
	arg++;
}

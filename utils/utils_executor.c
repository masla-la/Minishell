/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamorr <jchamorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:16:40 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/29 15:23:31 by jchamorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_child_1(t_mini *mini, int fd[2], t_list *lst)
{
	if (lst->output > 0)
		dup2(lst->output, 1);
	else
		dup2(fd[WRITE], STDOUT_FILENO);
	if (lst->input > 0)
		dup2(lst->input, STDIN_FILENO);
	close(fd[WRITE]);
	ft_redir_ex(mini, lst);
}

void	ft_child_2(t_mini *mini, int fd[2], int fd2[2], t_list *lst)
{
	close(fd[READ]);
	close(fd2[WRITE]);
	dup2(fd[WRITE], STDOUT_FILENO);
	dup2(fd2[READ], STDIN_FILENO);
	ft_redir_ex(mini, lst);
}

void	ft_child_3(t_mini *mini, int fd[2], t_list *lst)
{
	close(fd[WRITE]);
	if (lst->output > 0)
		dup2(lst->output, 1);
	if (lst->input > 0)
		dup2(lst->input, STDIN_FILENO);
	else
		dup2(fd[READ], STDIN_FILENO);
	ft_redir_ex(mini, lst);
}

void	ft_reddir_childs(t_mini *mini, int fd[2], int fd2[2], t_list *lst)
{
	if (mini->lst->content[0] == lst->content[0] && lst->next)
		ft_child_1(mini, fd, lst);
	else if (!lst->next)
		ft_child_3(mini, fd2, lst);
	else
		ft_child_2(mini, fd, fd2, lst);
}

int	ft_ex_bin(t_mini *mini, t_list *lst)
{
	int		i;
	char	*path;
	char	*cmd_path;

	i = 0;
	while (mini->path && mini->path[i])
	{
		path = ft_strjoin(mini->path[i], "/");
		cmd_path = ft_strjoin(path, lst->content[0]);
		execve(cmd_path, lst->content, mini->env);
		free(cmd_path);
		i++;
	}
	if (lst->content[0])
		execve(lst->content[0], lst->content, mini->env);
	printf("Minishell: command not found: %s\n", lst->content[0]);
	return (EXIT_FAILURE);
}

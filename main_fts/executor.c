/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamorr <jchamorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:43:02 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/29 16:44:45 by jchamorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tml_executor(t_mini *mini, int *fd, t_list *lst)
{
	signal(SIGINT, sig_child);
	signal(SIGIOT, sig_child);
	signal(SIGQUIT, sig_child);
	ft_reddir_childs(mini, lst->fd, fd, lst);
	exit(127);
}

int	ft_executor(t_mini *mini)
{
	t_list	*lst;
	int		*fd;

	lst = mini->lst;
	signal(SIGINT, ft_sig2);
	while (lst && lst->content[0] != NULL)
	{
		pipe(lst->fd);
		if (!is_builting(lst->content[0], lst))
			lst->pid = fork();
		if (!lst->pid && !is_builting(lst->content[0], lst))
			tml_executor(mini, fd, lst);
		else if (is_builting(lst->content[0], lst))
			ft_redir_b(mini, lst);
		if (lst->pid && !is_builting(lst->content[0], lst))
			close(lst->fd[WRITE]);
		fd = lst->fd;
		lst = lst->next;
	}
	ft_wait_childs(mini);
	return (EXIT_SUCCESS);
}

int	ft_pipe_con(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == 124 && s[i + 1] != 32 && s[i - 1] != 32)
			j += 2;
		if (s[i] == 124 && s[i + 1] != 32 && s[i - 1] == 32)
			j++;
		if (s[i] == 124 && s[i - 1] != 32 && s[i - 1] != 32)
			j++;
		i++;
	}
	return (j + 1);
}

char	*ft_expand_pipes_2(char *cmd)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof (char *) * ft_strlen(cmd) + ft_pipe_con(cmd));
	while (cmd[i])
	{
		if (cmd[i] == '|' && cmd[i - 1] != 32)
		{
			tmp[j++] = 32;
			tmp[j++] = cmd[i++];
		}
		else
			tmp[j++] = cmd[i++];
	}
	free (cmd);
	tmp[j] = '\0';
	return (tmp);
}

char	*ft_expand_pipes(char *cmd)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof (char *) * ft_strlen(cmd) + ft_pipe_con(cmd));
	while (cmd[i])
	{
		if (cmd[i] == '|' && cmd[i + 1] != 32 && cmd[i + 1])
		{
			tmp[j++] = cmd[i++];
			tmp[j++] = 32;
		}
		else
			tmp[j++] = cmd[i++];
	}
	free (cmd);
	tmp[j] = '\0';
	return (tmp);
}

#include "../minishell.h"

// AQUI PAPI
void	ft_child_1(t_mini *mini, int fd[2], t_list *lst)
{
	printf("HAGO COSAS\n");
	printf("%d\n", dup2(fd[WRITE], STDOUT_FILENO)); // SEMUEEEEEEEEEEREEEEEEEEEE
	printf("HAGO COSAS 2 \n");
	close(fd[READ]);
	// Me muero aquí.
	//close(fd[WRITE]);
	ft_redir_ex(mini, lst);
}

void	ft_child_2(t_mini *mini, int fd[2], int fd2[2], t_list *lst)
{
	printf("CHILD 2\n");
	close(fd[READ]);
	close(fd2[WRITE]);
	dup2(fd[WRITE], STDOUT_FILENO);
	dup2(fd2[READ], STDIN_FILENO);
	ft_redir_ex(mini, lst);
}

void	ft_child_3(t_mini *mini, int fd[2], t_list *lst)
{
	printf("CHILD 3\n");
	close(fd[WRITE]);
	printf("HE CERRADO EL WRITE\n");
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
	if (!mini->path)
	{
		printf("NO HAY PATH PELELE\n"); /////////////////////////////
		return (EXIT_FAILURE);
	}
	while (mini->path[i])
	{
		path  = ft_strjoin(mini->path[i], "/");
		cmd_path = ft_strjoin(path, lst->content[0]);
		execve(cmd_path, lst->content, mini->env);
		free(cmd_path);
		i++;
	}
	if (lst->content[0])
		execve(lst->content[0], lst->content, mini->env);
	printf("Error\n");
	return (EXIT_FAILURE);
}

/*int	ft_redir_ex(t_mini *mini)
{
	char	**path;
	char	*cmd_path;

	path = ft_split(ft_find_env(mini, "PATH"), ':');
	while (*path)
	{
		cmd_path = ft_strjoin(*path, "/");
		execve(ft_strjoin(cmd_path, mini->lst->content[0]), mini->lst->content, mini->env);
		path++;
	}
	free(path);
	free(cmd_path);
	printf("Error\n");
	return (1);
}*/

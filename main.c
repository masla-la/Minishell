#include "minishell.h"

t_signal	g_signal;

void	ft_sig(int sig)
{
	if (sig == 2)
	{
		g_signal.siginit = 1;
		if (g_signal.pid_line)
			kill(g_signal.pid_line, SIGKILL);
	}
	else if (sig)
		exit(0);
}

int	ft_executor(t_mini *mini)
{
	t_list	*lst;
	int		*fd;

	lst  = mini->lst;
	while (lst)
	{
		pipe(lst->fd);
		lst->pid = fork();
		if (lst->pid == 0)
			ft_reddir_childs(mini, lst->fd, fd, lst);//agregar errores
		if (lst->pid != 0)
			close(lst->fd[WRITE]);
		fd = lst->fd;
		lst = lst->next;
	}
	ft_wait_childs(mini);
	return (EXIT_SUCES);
}

int	ft_init(t_mini *mini)
{
	char	*comand;

	while (g_signal.siginit == 0)//
	{
		ft_init_var(mini);
		comand = readline("\033[0;31mMiniShell: \033[0;37m");
		if (!comand || g_signal.siginit)
			break ;
		else
			add_history(comand);
		mini->comand = ft_split_exp(comand, ' ');
		free(comand);
		if (!mini->comand)
			return (EXIT_FAILURE);
		if (ft_parse(mini, mini->comand) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ft_executor(mini) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		ft_free_lst(mini->lst);
		ft_free_comand(mini);
	}
	ft_free_exprt(mini->exprt);
	return (EXIT_SUCES);
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;
	(void)ac;
	(void)av;
	
	mini.env = env;
	g_signal.siginit = 0;
	signal(SIGINT, ft_sig);
	if (ft_get_env(&mini, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_init(&mini) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCES);
}

//agregar señales
//ignorar las redirecciones dando valor a los outputs e intputs
//ejecutar codigo *
//extender env
//agregar $? con a ft de error

// 1 =  permiso denegado
// 130 = cntl + c
//127 = comando no existente
//257 = error al ejecutar comando
//investigar
//https://www.cyberciti.biz/faq/linux-bash-exit-status-set-exit-statusin-bash/

//dar el valor de error a g_signal.sigexit
//lo q implica cambiar la variable global
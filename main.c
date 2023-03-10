#include "minishell.h"

t_signal	g_signal;

// Gestiona las señales
void	ft_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		write(1, "\033[0;31mMiniShell: \033[0;37m", 25);
		//rl_on_new_line();
		/*g_signal.siginit = 1;
		if (g_signal.pid_line)
			kill(g_signal.pid_line, SIGKILL);*/
	}
	if (sig == SIGQUIT)
		exit(0);
}

// Crea los procesos "hijos"
int	ft_executor(t_mini *mini)
{
	t_list	*lst;
	int		*fd;

	lst  = mini->lst;
	while (lst)
	{
		if (!is_builting(lst->content[0]))
		{
			pipe(lst->fd);
			lst->pid = fork();
			if (lst->pid == 0)
			{
				ft_reddir_childs(mini, lst->fd, fd, lst);//agregar errores
				exit(0);//temp, evita crear procesos de más durante las pruevas
			}
			if (lst->pid != 0)
				close(lst->fd[WRITE]);
			fd = lst->fd;
		}
		else
			ft_redir_ex(mini, lst);
		lst = lst->next;
	}
	ft_wait_childs(mini);
	return (EXIT_SUCES);
}

// Gestiona el input (readline) y redirije al Parser y Executer
int	ft_init(t_mini *mini)
{
	char	*comand;

	while (g_signal.siginit == 0)//
	{
		ft_init_var(mini);
		comand = readline("\033[0;31mMiniShell: \033[0;37m");
		if (comand[0] == '\0')//
			comand = NULL;
		else
			add_history(comand);
		mini->comand = ft_split_exp(comand, ' ');
		free(comand);
		if (!mini->comand || mini->comand[0] == NULL)
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
	signal(SIGINT, ft_sig);//
	signal(SIGQUIT, ft_sig);
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

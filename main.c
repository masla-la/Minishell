/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamorr <jchamorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:38:45 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/09 11:22:56 by jchamorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Gestiona las señales

/*void	ft_sig(int sig)
{
	if (sig == SIGINT)
	{
		//write(1, "\n", 1);
		//write(1, "\033[0;31mMiniShell: \033[0;37m", 25);
		//rl_on_new_line();
		g_signal.siginit = 1;
		if (g_signal.pid_line)
			kill(g_signal.pid_line, SIGKILL);
	}
	if (sig == SIGQUIT)
		exit(0);
}*/

// Crea los procesos "hijos"
void	ft_pid_pipe(t_list *lst)
{
	pipe(lst->fd);
	lst->pid = fork();
}

// Significa Too_Many_Lines_executor()
void	tml_executor(t_mini *mini, int *fd, t_list *lst)
{
	signal(SIGINT, sig_child);
	signal(SIGIOT, sig_child);
	ft_reddir_childs(mini, lst->fd, fd, lst);
	exit(g_sig);
}

int	ft_executor(t_mini *mini)
{
	t_list	*lst;
	int		*fd;

	lst = mini->lst;
	signal(SIGINT, ft_sig2);
	while (lst)
	{
		pipe(lst->fd);
		if (!is_builting(lst->content[0]))
			lst->pid = fork();
		if (!lst->pid && !is_builting(lst->content[0]))
			tml_executor(mini, fd, lst);
		else if (is_builting(lst->content[0]))
		{
			ft_reddir_childs(mini, lst->fd, fd, lst);
			if (!ft_strcmp("exit", lst->content[0]))
				exit (g_sig);
		}
		if (lst->pid)
			close(lst->fd[WRITE]);
		fd = lst->fd;
		lst = lst->next;
	}
	ft_wait_childs(mini);
	return (EXIT_SUCCESS);
}

// Gestiona el input (readline) y redirije al Parser y Executer
int	ft_init(t_mini *mini)
{
	char	*comand;

	while (!g_sig) //
	{
		signal(SIGINT, ft_sig);
		ft_init_var(mini);
		comand = readline("\033[0;31mMiniShell: \033[0;37m");
		if (!comand) //
			return (EXIT_FAILURE);
		mini->comand = ft_split_exp(comand, ' ');
		if (mini->comand[0])
			add_history(comand);
		free(comand);
		if (mini->comand && mini->comand[0] != NULL)
		{
			ft_parse(mini, mini->comand);
			ft_executor(mini);
			ft_free_lst(mini->lst);
			ft_free_comand(mini);
		}
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
	g_sig = 0;
	signal(SIGQUIT, SIG_IGN); //'^\'
	signal(SIGIOT, sig_rl);   //^D
	signal(SIGTSTP, SIG_IGN); //^Z
	if (ft_get_env(&mini, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_init(&mini);
	return (g_sig);
}

//agregar señales
//ignorar las redirecciones dando valor a los outputs e intputs
//ejecutar codigo *
//extender env *
//agregar $? con a ft de error

//Built-ins en mayusculas debe interpretarse

//ls | cd .. | wc
//	0	0	0

// 1 =  permiso denegado
// 130 = cntl + c
//127 = comando no existente
//257 = error al ejecutar comando
//investigar
//https://www.cyberciti.biz/faq/linux-bash-exit-status-set-exit-statusin-bash/

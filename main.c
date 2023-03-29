/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masla-la <masla-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:38:45 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/29 11:13:28 by masla-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	g_sig; */

// Significa Too_Many_Lines_executor()
void	tml_executor(t_mini *mini, int *fd, t_list *lst)
{
	signal(SIGINT, sig_child);
	signal(SIGIOT, sig_child);
	ft_reddir_childs(mini, lst->fd, fd, lst);
	exit(127);
}

int	ft_executor(t_mini *mini)
{
	t_list	*lst;
	int		*fd;

	lst = mini->lst;
	signal(SIGINT, ft_sig2);
	while (lst && lst->content[0] != NULL) //error para multiles pipes seguidas
	{
		pipe(lst->fd);
		if (!is_builting(lst->content[0], lst))
			lst->pid = fork(); // si no el builting proceso hijo, si no perdemos datos
		if (!lst->pid && !is_builting(lst->content[0], lst))
			tml_executor(mini, fd, lst); // Si es proceso hijo y no es builting lanza las señale y tira el proceso
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

// Cuenta las pipe sin espacio después pero devuelve +1 para el NULL de malloc
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

char	*ft_readline(char *name)
{
	char	*cmd;

	cmd = readline(name);
	if (!cmd)
			return (NULL);
	cmd = ft_strtrim(cmd, " ");
	if (cmd && cmd[0] != '\0')
		add_history(cmd);
	if (ft_strchr(cmd, 124) && !ft_strchr(cmd, 34) && !ft_strchr(cmd, 39))
	{
		cmd = ft_expand_pipes(cmd);
		cmd = ft_expand_pipes_2(cmd);
	}
	return (cmd);
}

// Gestiona el input (readline) y redirije al Parser y Executer
int	ft_init(t_mini *mini)
{
	char	*comand;

	while (!g_sig)
	{
		signal(SIGINT, ft_sig);
		ft_init_var(mini);
		comand = ft_readline("\033[0;31mMiniShell: \033[0;37m");
		if (!comand)
			return (sig_rl(comand, mini));
		mini->comand = ft_split_quotes(comand, ' ');
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
	print_pepe("PrintPepe/pepe");
	mini.env = env;
	g_sig = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	if (ft_get_env(&mini, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_init(&mini);
	return (g_sig);
}

/* Cosas que se rompren o que he roto:
	- He puesto unset ENV y segfault
	- Si usas /bin/ls lo tiene que hacer aunque elimines el PATH
	- expr $? + $?
	- El ctrl + D da leaks pero 'exit' no, asi que hay que mandar la señal a que haga el exit normal.
	- Los fallos de '/bin/ls pepe' tiene que dar el mismo error que bash.
*/

// ignorar las redirecciones dando valor a los outputs e intputs
// ejecutar codigo *
// agregar $? con a ft de error

//Built-ins en mayusculas debe interpretarse

//https://www.cyberciti.biz/faq/linux-bash-exit-status-set-exit-statusin-bash/

//Contador de comillas

//gestionar las salidas de error

//ft_rm_to_env se peta si no encuentra el env, almenos con unset
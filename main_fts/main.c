/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masla-la <masla-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:38:45 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/30 13:02:02 by masla-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_readline(char *name)
{
	char	*cmd;

	cmd = readline(name);
	if (!cmd)
	{
		free(cmd);
		return (NULL);
	}
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

int	ft_init(t_mini *mini)
{
	char	*comand;

	while (!g_sig)
	{
		signal(SIGINT, ft_sig);
		ft_init_var(mini);
		comand = ft_readline("MiniShell: ");
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

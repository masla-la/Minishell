/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masla-la <masla-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:41:43 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/30 12:52:59 by masla-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_child(int sig)
{
	if (sig == SIGINT || sig == SIGIOT)
	{
		close(WRITE);
		exit(1);
	}
}

int	sig_rl(char	*c, t_mini *mini)
{
	free(c);
	ft_free_pepe(mini);
	ft_free_exprt(mini->exprt);
	ft_free_lst(mini->lst);//
	g_sig = 1;
	rl_replace_line("exit", 0);
	print_pepe("PrintPepe/pepe2");
	printf("Minishell: exit\n");
	return (1);
}

void	ft_sig2(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	ft_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

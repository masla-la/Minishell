/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masla-la <masla-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:00:15 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/24 10:33:57 by masla-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builting(char *c, t_list *lst)
{
	if (!ft_strcmp("cd", c) && !lst->next)
		return (1);
	else if (!ft_strcmp("export", c) && lst->content[1])
		return (1);
	else if (!ft_strcmp("unset", c))
		return (1);
	else if (!ft_strcmp("exit", c) && !lst->next)
		return (1);
	return (0);
}

int	ft_redir_b(t_mini *mini, t_list *lst)
{
	if (!ft_strcmp("cd", lst->content[0]) && !lst->next)
		return (ft_cd(mini, lst));
	if (!ft_strcmp("export", lst->content[0]))
		return (ft_add_to_env(mini, lst->content[1]));
	else if (!ft_strcmp("unset", lst->content[0]))
		return (ft_rm_to_env(mini, lst->content[1]));
	else if (!ft_strcmp("exit", lst->content[0]))
	{
		if (lst->content[1] && ft_isnum(lst->content[1]))
			exit ((g_sig = ft_atoi(lst->content[1])));
		if (lst->content[1] && !ft_isnum(lst->content[1]))
			ft_exit_error(mini, 2);
		exit ((g_sig = 1));
	}
	return (0);
}

int	ft_redir_ex(t_mini *mini, t_list *lst)
{
	if (!ft_strcmp("env", lst->content[0]))
		return (ft_print_env(mini));
	else if (!ft_strcmp("cd", lst->content[0]))
		return (ft_cd(mini, lst));
	else if (!ft_strcmp("pwd", lst->content[0]))
		return (printf("%s\n", ft_find_env(mini, "PWD")));
	else if (!ft_strcmp("echo", lst->content[0]))
		return (ft_echo(lst));
	else if (!lst->content[1] && !ft_strcmp("export", lst->content[0]))
		return (order_env(mini));
	else if (!ft_strcmp("exit", lst->content[0]))
	{
		if (lst->content[1] && ft_isnum(lst->content[1]))
			return ((g_sig = ft_atoi(lst->content[1])));
		if (lst->content[1] && !ft_isnum(lst->content[1]))
			ft_exit_error(mini, 2);
		return ((g_sig = 1));
	}
	return (ft_ex_bin(mini, lst));
}

//export no tiene mensaje de error al ser numero
//cd no tiene mensaje si no tiene acceso
//unset no tiene mensaje sin arg
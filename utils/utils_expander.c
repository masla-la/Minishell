/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masla-la <masla-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:42:28 by jchamorr          #+#    #+#             */
/*   Updated: 2023/04/03 12:26:37 by masla-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_reddir_input(t_mini *mini, char *arg, t_list *lst)
{
	lst->input = open(arg, O_RDONLY);
	if (!access(arg, F_OK))
		ft_exit_error(mini, '1');
}

void	ft_reddir_output(t_mini *mini, char *arg, t_list *lst)
{
	lst->output = open(arg, O_RDWR);
	if (!access(arg, F_OK))
		ft_exit_error(mini, '1');
}

void	ft_reddir_input_2(t_mini *mini, char *arg, t_list *lst)
{
	lst->input = open(arg, O_WRONLY | O_APPEND | O_CREAT, 0660);
	lst->index = 2;
	lst->delimiter = ft_strdup(arg);
	here_doc(lst->input, lst->delimiter);
	if (!access(arg, F_OK))
		ft_exit_error(mini, '1');//
}

void	ft_reddir_output_2(t_mini *mini, char *arg, t_list *lst)
{
	lst->output = open(arg, O_CREAT | O_WRONLY, 0666);
	here_doc2(lst->output, arg);
	if (!access(arg, F_OK))
	{
		printf("ACCESS = %d\n", access(arg, F_OK));
		printf("ACCESS ERROR\n");
		ft_exit_error(mini, '1');
	}
}

void	ft_reddir(t_mini *mini, char **arg, t_list *lst, int i)
{
	lst->index = 1;
	if (!ft_strncmp(lst->content[0], "echo", 4) && lst->content[1])
	{
		ft_free_content(lst, arg[i - 1]);
		lst->content[0] = (arg[i - 1]);
		lst->content[1] = NULL;
	}
	// comprobar el builting
	if (!ft_strcmp(arg[i], "<<"))
	{
		printf("ENTRAMOS AQUI 1\n");
		ft_reddir_input_2(mini, arg[i + 1], lst);
	}
	else if (!ft_strcmp(arg[i], ">>"))
	{
		printf("ENTRAMOS AQUI 2\n");
		ft_reddir_output_2(mini, arg[i + 1], lst);
	}
	else if (ft_strchr(arg[i], '<'))
	{
		printf("ENTRAMOS AQUI 3\n");
		ft_reddir_input(mini, arg[i + 1], lst);
	}
	else if (ft_strchr(arg[i], '>'))
	{
		printf("ENTRAMOS AQUI 4\n");
		ft_reddir_output(mini, arg[i + 1], lst);
	}
	i++;
}

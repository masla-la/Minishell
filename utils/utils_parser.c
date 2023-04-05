/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masla-la <masla-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:46:32 by jchamorr          #+#    #+#             */
/*   Updated: 2023/04/05 10:52:03 by masla-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_arg_len(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] && ft_strcmp2(arg[i], "|"))
		i++;
	return (i + 1);
}

int	ft_add_something(t_list **linked, int len, int i)
{
	t_list	*new;
	t_list	*copy;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->content = malloc(sizeof(char *) * len);
	new->next = NULL;
	copy = (*linked);
	while (copy->next)
		copy = copy->next;
	copy->content[i] = NULL;
	copy->next = new;
	return (0);
}

//Hay que darle una vuelta a ésto
int	ft_parse_to_lst(t_mini *mini, char **arg, int j)
{
	t_list	*lst;
	int i;

	i = 0;
	lst = ft_lstnew(NULL);
	mini->lst = lst;
	lst->content = malloc(sizeof(char *) * ft_arg_len(arg));
	lst->index = 0;
	while (arg && arg[i])
	{
		printf("%s\n", *arg);
		if (!ft_strcmp2(arg[i], "<") || !ft_strcmp2(arg[i], ">") ||\
		!ft_strcmp2(arg[i], ">>") || !ft_strcmp2(arg[i], "<<"))
			ft_reddir(mini, arg, lst, i);
		else if (ft_strcmp2(arg[i], "|") && lst->index == 0 && arg[i] != NULL)
			lst->content[j++] = ft_strdup(arg[i]);
		else if (!ft_strcmp2(arg[i], "|") && (arg[i + 1]))
		{
			printf("123\n");
			j = ft_add_something(&lst, ft_arg_len(&arg[i + 1]), j);
			lst = lst->next;
			lst->index = 0;
		}
		i++;
	}
	//
	i = 0;
	while (arg[i++])
		printf("ARG REDDIR = %s\n", arg[i]);
	//
	lst->content[j] = NULL;
	printf("ARG CONTENT = %s\n", *lst->content);
	return (EXIT_SUCCESS);
}

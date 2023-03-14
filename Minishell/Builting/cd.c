/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamorr <jchamorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:00:06 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/13 19:02:18 by jchamorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_update_pwd(t_mini *mini)
{
	t_exprt	*exprt;
	char	*cpy;
	char	pwd[2056];
	char	*tmp;

	exprt = mini->exprt;
	while (exprt->next)
	{
		if (!ft_strncmp("PWD", exprt->env, 3))
		{
			cpy = ft_strjoin2("OLD", exprt->env);
			free(exprt->env);
			getcwd(pwd, sizeof(pwd));
			tmp = ft_strjoin2("PWD=", pwd);
			exprt->env = ft_strdup(tmp);
			free(tmp);
		}
		if (!ft_strncmp("OLDPWD", exprt->env, 6))
		{
			free(exprt->env);
			exprt->env = ft_strdup(cpy);
			free(cpy);
		}
		exprt = exprt->next;
	}
}

char	*ft_cd_return(char *str)
{
	int		i;
	int		n;
	char	*dest;

	i = ft_strlen(str);
	while (str[i] != '/')
		i--;
	dest = malloc(sizeof(char *) * i + 1);
	n = 0;
	while (n < i)
	{
		dest[n] = str[n];
		n++;
	}
	dest[n] = '\0';
	return (dest);
}

char	*ft_join_dir(char *str, t_list *lst)
{
	char	*tmp;
	char	*dest;

	tmp = ft_strjoin(str, "/");
	dest = ft_strjoin(tmp, lst->content[1]);
	if (!dest)
		return (NULL);
	return (dest);
}

int	ft_cd(t_mini *mini, t_list *lst)
{
	char	*dest;
	char	str[2056];

	dest = NULL;
	if (lst->content[1])
	{
		getcwd(str, sizeof(str));
		if (!ft_strncmp("..", lst->content[1], 2))
			dest = ft_cd_return(str);
		else
			dest = ft_strdup(lst->content[1]);
	}
	else
		dest = ft_find_env(mini, "HOME");
	if (!access(dest, F_OK))
	{
		chdir(dest);
		ft_update_pwd(mini);
	}
	free(dest);
	return (EXIT_SUCCESS);
}

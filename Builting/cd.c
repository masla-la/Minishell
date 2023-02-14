#include "../minishell.h"

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

int	ft_cd(t_mini *mini, t_list *lst)
{
	char	*dest;
	char	*str;

	dest = NULL;
	str = NULL;
	if (lst->content[1])
	{
		str = malloc(sizeof(char *));
		getcwd(str, 100);
		if (!ft_strncmp("..", lst->content[1], 2))
			dest = ft_cd_return(str);
		else
			dest = ft_strjoin(str, lst->content[1]);//comprobar acceso
		free(str);
	}
	else
		dest = ft_find_env(mini, "HOME");//
	if (access(dest, F_OK))
		chdir(dest);
	free(dest);
	return (EXIT_SUCCESS);
}

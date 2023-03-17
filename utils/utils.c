#include "../minishell.h"

char	*ft_strdup2(const char *src)//quita las comillas si existen
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * (ft_strlen((src)) + i + 100000));
	if (!dest)
		return (NULL);
	if (*src == 39 || *src == 34)
		src++;
	i = 0;
	while (src[i] != 00)
	{
		if (!src[i + 1] && (src[i] == 34 || src[i] == 39))
			break ;
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_init_var(t_mini *mini)
{
	char	*path;

	path = ft_find_env(mini, "PATH");
	mini->path = ft_split(path, ':');
	free(path);
}

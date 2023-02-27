#include "../minishell.h"

char	*ft_strdup(const char *src)//quita los parentesis si existen
{
	char	*dest;
	int		i;

	i = 0;
	if (src[0] == 34 || src[0] == 39)
		i = -2;
	dest = malloc(sizeof(char) * (ft_strlen((src)) + i + 1));
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

#include "minishell.h"

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

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

int	ft_strncmp(char const *s1, char const *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return (1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		c;
	char	*dest;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc(sizeof(char) * (i + 1));
	i = -1;
	while (s1[++i])
		dest[i] = s1[i];
	c = -1;
	while (s2[++c])
		dest[i + c] = s2[c];
	dest[i + c] = '\0';
	return (dest);
}

void	ft_init_var(t_mini *mini)
{
	char	*path;

	path = ft_find_env(mini, "PATH");
	mini->path = ft_split(path, ':');
	free(path);
}

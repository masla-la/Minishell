#include "minishell.h"

char	*ft_cpy_rest(char *arg, char *dest)
{
	int		i;
	int		n;
	char	*cpy;

	i = -1;
	n = 0;
	while (arg[++i])
	{
		if (arg[i] == '$')
		{
			while (arg[i + n] && arg[i] == '$' && arg[i + n] != ' ')
				n++;
			i += n;
			break ;
		}
	}
	if (!arg[i])
		return (dest);
	cpy = ft_strjoin(dest, arg + i);
	free(dest);
	return (cpy);
}

char	*ft_strdup_len(char const *str, int len)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char *) * len + 1);
	while (i < len)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_cpy_var(char *ptr)
{
	char	*var;
	int		i;

	i = 0;
	while (ptr[i] && ptr[i] != ' ')
		i++;
	if (i < 1)
		return (NULL);
	var = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (ptr[i] && ptr[i] != ' ' && ptr[i] != 34)
	{
		var[i] = ptr[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

char	*ft_join_path(char *s1, char *s2)
{
	int		i;
	int		n;
	char	*cpy;
	char	*dest;

	i = 0;
	n = 0;
	cpy = NULL;
	if (!s1 && !s2)
		return (NULL);
	while (s1[i] && s1[i] != '$')
		i++;
	if (i > 0)
		cpy = ft_strdup_len(s1, i);
	if (!cpy)
		return (s2);
	if (!s2)
		return (cpy);
	dest = ft_strjoin(cpy, s2);
	free(cpy);
	return (dest);
}

char	*ft_expand(char *arg, t_mini *mini)
{
	int		i;
	char	*path;
	char	*var;
	char	*arg_cpy;
	char	*dest;

	i = -1;
	arg_cpy = ft_strdup(arg);
	while (arg[0] != 39 && arg_cpy[++i])
	{
		if (arg_cpy[i] == '$')
		{
			var = ft_cpy_var(arg_cpy + (i + 1));
			path = ft_find_env(mini, var);
			dest = ft_join_path(arg_cpy, path);
			dest = ft_cpy_rest(arg_cpy, dest);
			free(path);
			free(var);
			free(arg_cpy);
			free(arg);
			return (ft_expand(dest, mini));
		}
	}
	free(arg);
	return (arg_cpy);
}
//no reconoce las comillas entre otras comillas, las separa.
//probleams con "123 ' 123"
//free invalid pointer en ls y "123' 123"

//sobran los utils de expander
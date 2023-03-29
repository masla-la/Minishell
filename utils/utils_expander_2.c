#include "../minishell.h"

/*char	*ft_sust(char *str, char c)
{
	int	i;
	int	n;
	char	*dest;

	i = ft_strlen(str) + 1;
	n = 0;
	while (str[n])
	{
		if (str[n] == c)
			i--;
		n++;
	}
	dest = (char *)malloc(sizeof(char) * i);
	n = 0;
	i = 0;
	while (str[n])
	{
		if (str[n] != c)
			dest[i++] = str[n];
		n++;
	}
	dest[i] = '\0';
	return (dest);
}*/

int	check_quote_to_expand(int quote, char *arg, int i)
{
	if (arg[i] == 39 && quote == 0)
		return (1);
	else if (arg[i] == 39 && quote == 1)
		return (0);
	return (quote);
}

int	check_dl(char *str, int i)
{
	int	n;

	n = i;
	while (str[n] && str[n] != ' ' && str[n] != ':'\
	&& str[n] != ';' && str[n] != '$' && str[n] != '\0')
		n++;
	if (n - 1 < i)
		return (0);
	return (1);
}

char	*ft_expand(char *arg, t_mini *mini)
{
	int		i;
	char	*arg_cpy;
	int		quote;

	i = -1;
	quote = 0;
	arg_cpy = ft_strdup2(arg);
	while (arg[++i])
	{
		quote = check_quote_to_expand(quote, arg, i);
		if (arg[i] == '$' && arg[i + 1] && quote == 0)
			if (check_dl(arg, i + 1))
				return (ft_expand_var(mini, arg, arg_cpy, i));
	}
	free(arg);
	return (arg_cpy);
}

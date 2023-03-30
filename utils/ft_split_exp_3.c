#include "../minishell.h"

char	**ft_exp(char **dst, char *s, char quote_type, int i[3])
{
	while (s[++i[0]])
	{
		while (s[i[0]] == ' ')
			i[0]++;
		if (s[i[0] + 1] && (s[i[0]] == 34 || s[i[0]] == 39))
		{
			i[2] = 1;
			quote_type = s[i[0]];
		}
		if (s[i[0]] != ' ' && i[2] == 0)
		{
			dst[i[1]++] = ft_strdup_space(s, ' ', i[0]);
			i[0] += ft_strlen(dst[i[1] - 1]) - 1;
		}
		else if (i[2] == 1)
		{
			dst[i[1]++] = ft_strdup_quote(s, i[0], quote_type);
			i[2] = 0;
			i[0] += ft_strlen(dst[i[1] - 1]) - 1;
		}
		if (s[i[0]] == '\0')
			break ;
	}
	dst[i[1]] = NULL;
	return (dst);
}

size_t	ft_exp_2(char *s, int i, int quotes, char c)
{
	while (*s != '\0')
	{
		if (*s == 34 || *s == 39)
		{
			if (quotes == *s && (*(s) == 34 || *(s + 1) == 39))
			{
				i++;
				if (*(s + 1) != '\0' && *(s + 1) != ' ')
					s++;
			}
			if (quotes == 0)
				quotes = *s;
			else if (quotes == *s)
				quotes = 0;
		}
		if (*s == c && quotes == 0 && *(s + 1) && *(s + 1) != 32)
		{
			i++;
			while (*s == c && *s != '\0')
				s++;
		}
		else
			s++;
	}
	return (i + 1);
}

#include "minishell.h"

static int	ft_count(long n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	if (n == 0)
		i++;
	while (n >= 1)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static char	*ft_set(char *dest, long n2, int i)
{
	size_t	c;
	int		neg;

	c = 0;
	neg = 0;
	if (n2 < 0)
	{
		dest[c] = '-';
		n2 = -n2;
		c++;
		neg = 1;
	}
	while (i > neg)
	{
		dest[i - 1] = (n2 % 10) + '0';
		n2 /= 10;
		i--;
		c++;
	}
	dest[c] = '\0';
	return (dest);
}

char	*ft_itoa(int n)
{
	char	*dest;
	size_t	i;
	long	n2;

	n2 = n;
	i = 0;
	i = ft_count(n);
	dest = malloc(i + 1);
	if (!dest)
		return (NULL);
	dest = ft_set(dest, n2, i);
	return (dest);
}

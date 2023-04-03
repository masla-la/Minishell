#include "../minishell.h"

int	here_doc(int fd, char *delimiter)
{
	char	*line;
	int		fd2[2];

	pipe(fd2);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) - 1))
		{
			free(line);
			break ;
		}
		write(fd2[1], line, ft_strlen(line));
		free(line);
	}
	close(fd2[1]);
	dup2(fd2[0], fd);
	close(fd2[0]);
	return (fd);
}

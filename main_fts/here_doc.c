#include "../minishell.h"

void	here_doc2(int fd, char *arg)
{
	char	*line;
	int		fd2;

	fd2 = open(arg, O_RDONLY);
	line = get_next_line(fd2);
	while (line)
	{
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(fd2);
	}
	free(line);
	close(fd2);
}

void	here_doc(int fd, char *delimiter)
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
}

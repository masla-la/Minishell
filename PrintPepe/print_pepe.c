#include  "../minishell.h"

void	print_pepe(char *n)
{
	int		fd;
	char	*line;

	fd = open(n, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("\x1b[32m%s\x1b[0m", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	printf("\n");
	close(fd);
}

#include  "../minishell.h"

void	print_pepe(void)
{
	int		fd;
	char	*line;

	fd = open("PrintPepe/pepe", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("\x1b[32m%s", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	printf("\n");
	close(fd);
}

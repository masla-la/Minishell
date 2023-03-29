/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pepe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamorr <jchamorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:14:42 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/29 14:14:43 by jchamorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

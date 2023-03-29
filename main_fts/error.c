/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamorr <jchamorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:38:01 by jchamorr          #+#    #+#             */
/*   Updated: 2023/03/29 17:46:56 by jchamorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	write_error(t_mini *mini, int err, char *str, char *str2)
{
	ft_putstr_fd(str, 2);
	if (str2)
		ft_putstr_fd(str2, 2);
	ft_putstr_fd("\n", 2);
	ft_exit_error(mini, err);
	return (err);
}

#include "../minishell.h"

// Comprueba si el comando es un built-in
int	is_builting(char *c)
{
	if (!ft_strncmp("env", c, 3))//
		return (1);
	else if (!ft_strncmp("cd", c, 2))//
		return (1);
	else if (!ft_strncmp("pwd", c, 3))//
		return (1);
	else if (!ft_strncmp("export", c, 6))
		return (1);//
	else if (!ft_strncmp("unset", c, 5))
		return (1);
	else if (!ft_strncmp("echo", c, 4))
		return (1);
	return (0);
}

// Redirige hacia los buit-ins o continua normalmente
int	ft_redir_ex(t_mini *mini, t_list *lst)
{
	if (!ft_strncmp("env", lst->content[0], 3))//
		return (ft_print_env(mini));
	else if (!ft_strncmp("cd", lst->content[0], 2))//
		return (ft_cd(mini, lst));
	else if (!ft_strncmp("pwd", lst->content[0], 3))//
		return (printf("%s\n", ft_find_env(mini, "PWD")));
	else if (!ft_strncmp("echo", lst->content[0], 4))
		return (ft_echo(lst));
	else if (!lst->content[1] && !ft_strncmp("export", lst->content[0], 6))
		return (ft_export_dcr(mini));//
	else if (!ft_strncmp("export", lst->content[0], 6))
		return (ft_add_to_env(mini, lst->content[1]));//
	else if (!lst->content[1] && !ft_strncmp("unset", lst->content[0], 5))
		return (EXIT_SUCCESS);
	else if (!ft_strncmp("unset", lst->content[0], 5))
		return (ft_rm_to_env(mini, lst->content[1]));
	return (ft_ex_bin(mini, lst));
}
//falta el echo
//export no tiene mensaje de error al ser numero
//cd no tiene mensaje si no tiene acceso

//unset no funciona

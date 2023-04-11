/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masla-la <masla-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:49:26 by jchamorr          #+#    #+#             */
/*   Updated: 2023/04/11 11:52:24 by masla-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define READ 0
# define WRITE 1
# define EXIT_FAILURE 1
# define EXIT_SUCES 0
# define REDIR_INPUT 3
# define REDIR_OUTPUT 3

# define STDIN	0
# define STDOUT	1

int		g_sig;

typedef struct s_mini
{
	char			**comand;
	char			**path;
	char			*cmd_path;
	int				pid;
	char			**env;
	struct s_exprt	*exprt;
	struct s_list	*lst;
}				t_mini;

typedef struct s_exprt
{
	char			*env;
	struct s_exprt	*next;
}				t_exprt;

//Utils_env
int		ft_get_env(t_mini *mini, char **env);
char	*ft_find_env(t_mini *mini, char *str);
t_exprt	*ft_lstnew_exp(void *content);
void	ft_lstadd_exp(t_exprt **exprt, t_exprt *new);

//Utils
int		check_env(char *str);
char	**ft_split_quotes(char *s, char c);
char	*ft_strdup2(const char *src);
void	ft_init_var(t_mini *mini);
int		ft_strcmp2(char *s1, char *s2);

//Split Utils
int		ft_cmd_len(char *s, int i);
void	final_split_condition(int *i, char **dst);
int		split_condition_2(char *type, char c);
char	**split_condition(char **dst, int *i, char *s);
int		another_condition(char *s, int *i, int in_quotes, char **dst);
int		split_condition_quote(char **dst, int *i, char *s);
char	**ft_exp(char **dst, char *s, char quote_type, int i[3]);
size_t	ft_exp_2(char *s, int i, int quotes, char c);

//Utils_lexer
int		ft_total_arg(char **ptr);//
int		ft_count_arg(char **ptr, int i);//
void	ft_count_pipes(t_mini *mini);//

//Utils_parser
int		ft_arg_len(char **arg);
int		ft_parse_to_lst(t_mini *mini, char **arg, int i);
int		check_quote_to_expand(int quote, char *arg, int i);
char	*ft_sust(char *str, char c);
char	*ft_expand_var(t_mini *mini, char *arg, char *arg_cpy, int i);

//Utils_expander
void	ft_reddir(t_mini *mini, char **arg, t_list *lst, int i);
char	*ft_expand(char *arg, t_mini *mini);

//Ft_free
void	ft_free_comand(t_mini *mini);
void	ft_free_exprt(t_exprt *exprt);
void	ft_free_lst(t_list *lst);
void	ft_free(t_mini *mini);
void	ft_free_content(t_list *lst, char *arg);
void	ft_free_pepe(t_mini *mini);

//Parser
int		ft_parse(t_mini *mini, char **arg);

//Executor
void	ft_reddir_childs(t_mini *mini, int fd[2], int fd2[2], t_list *lst);
void	ft_wait_childs(t_mini *mini);
int		ft_redir_ex(t_mini *mini, t_list *lst);
int		ft_ex_bin(t_mini *mini, t_list *lst);
int		ft_redir_b(t_mini *mini, t_list *lst);

//Error
int		ft_exit_error(t_mini *mini, int error);
int		write_error(t_mini *mini, int err, char *str, char *str2);

//Builtings
int		ft_cd(t_mini *mini, t_list *lst);
int		ft_echo(t_list *lst);
int		ft_rm_to_env(t_mini *mini, char *str);
int		ft_print_env(t_mini *mini);
int		ft_add_to_env(t_mini *mini, char *str);
int		order_env(t_mini *s);
void	print_export(char **export);
int		is_builting(char *c, t_list *lst);
int		ft_isnum(const char *str);

//Signals
void	sig_child(int sig);
void	ft_sig(int sig);
void	ft_sig2(int sig);
int		sig_rl(char *c, t_mini *mini);

//FT que faltan por nombrar
int		write_error(t_mini *mini, int err, char *str, char *str2);//
char	*ft_strdup_space(char *s, char c, int start);
char	*ft_strdup_quote(char *s, int start, char quote_type);
int		init_vars(int *i, char **dst, char *s);
char	*ft_expand_pipes(char *cmd);
char	*ft_expand_pipes_2(char *cmd);
int		ft_executor(t_mini *mini);
char	*ft_cpyn(char *s, int start, int end);
size_t	ft_lines_2(char *s, char c, int quotes);
int		is_quote_closed(char *s);
char	**ft_fill_2(char **dst, char *s);
char	*ft_rm_first_pipe(char *str);

//Pepe
void	print_pepe(char *n);

//Here_doc
void	here_doc(int fd, char *delimiter);
void	here_doc2(int fd, char *arg);

#endif
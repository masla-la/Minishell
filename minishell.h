#ifndef MINISHELL_H
#define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>//
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

typedef struct	s_mini
{
	char			**comand;
	char			**path;
	char			*cmd_path;
	int				pid;//
	char			**env;
	struct	s_exprt	*exprt;
	struct	s_list	*lst;
}				t_mini;

typedef struct	s_list
{
	char			**content;
	int				input;//
	int				output;//
	int				pid;
	int				fd[2];
	struct	s_list	*next;
}				t_list;

typedef struct	s_exprt
{
	char			*env;
	struct	s_exprt	*next;
}				t_exprt;

typedef	struct	s_signal
{
	int		siginit;
	pid_t	pid_line;
}				t_signal;

//Utils_env
int		ft_get_env(t_mini *mini, char **env);
char	*ft_find_env(t_mini *mini, char *str);
t_exprt	*ft_lstnew_exp(void *content);
void	ft_lstadd_exp(t_exprt **exprt, t_exprt *new);

//Utils
char	*ft_strdup(const char *src);
size_t	ft_strlen(const char *c);
int		ft_strncmp(char const *s1, char const *s2, int n);//modificar
char	**ft_split(char const *s, char c);
char	**ft_split_exp(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);//
void	ft_init_var(t_mini *mini);

//Utils_lexer
int		ft_total_arg(char **ptr);
int		ft_count_arg(char **ptr, int i);
void	ft_count_pipes(t_mini *mini);
int		ft_lexer(t_mini *mini, t_list *lst);

//Utils_expander
void	ft_reddir(t_mini *mini, char **arg, t_list *lst);
//int		ft_expander(t_mini *mini, t_list *lst, t_cmd *cmd);


//Ft_free
void	ft_free_comand(t_mini *mini);
void	ft_free_exprt(t_exprt *exprt);
void	ft_free_lst(t_list *lst);
void	ft_free(t_mini *mini);

int		ft_parse(t_mini *mini, char **arg);
char	*ft_expand(char *arg, t_mini *mini);

void	ft_reddir_childs(t_mini *mini, int fd[2], int fd2[2], t_list *lst);
int		ft_redir_ex(t_mini *mini, t_list *lst);
void	ft_wait_childs(t_mini *mini);

int		ft_exit_error(t_mini *mini, int	error);
int		ft_add_to_env(t_mini *mini, char *str);



#endif
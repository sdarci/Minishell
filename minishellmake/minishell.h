#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# define COLOR_ORANGE "\x1b[38;5;208m"
# define COLOR_RED				"\x1b[38;5;196m"
# define COLOR_RESET			"\x1b[0m"
# define STDIN		0
# define STDOUT		1
# define STDERR		2
# define ISSPACE	"\t\n\v\f\r "
# include "parsing/LIBFT/libft.h"

typedef struct env1
{
	char		*key;
	char		*value;
	struct env1	*next;
}	t_env;

typedef struct s_list
{
	void			*data;
	int				type;
	struct s_list	*next;
}	t_list;

typedef struct s_redir
{
	char			*in; // файл, из которого команда берет данные (NULL если такого файла нет)
	char			*out; // файл, в который команда отдает результат (NULL если такого файла нет)
	int				type_in; // 3 - файл, 4 - хередок
	int				type_out;// 1 - перезаписываем, 2 - дозаписываем
}	t_redir;

typedef struct s_tok
{
	int				total;
	int				num;
	char			**env;
	int				flag_l;
	int				flag_r;
	int				flag_dub_r;
	int				flag_dub_l;
	int				flag_q;
	int				flag_dub_q;
	char			*line;
	char			*cmd;
	char			**cmd_arr;
	//int				f_build_in;
	t_redir			*red;//содержит инпут и аутпут для команды
	t_list			*check; // список файлов, которые нужно проверить на наличие и открыть, если их нет - вернуть ошибку
	t_list			*create;// список файлов, которые нужно проверить на наличие и открыть, если их нет - создать
	struct s_tok	*next;
}	t_tok;

typedef struct s_data
{
	int		total_pipe;
	t_tok	*tokens;
	t_list	*bildins;
}	t_data;

typedef struct s_shell
{
	char		*prompt_name;
	char		*prompt_line;
	char		*input;
	char		*line;
	int			status;
	char		**copy_env;
	t_env		*env1;
	int			exit_status;
	t_tok		*cmd;
	int			fd_her;
	char		*heredoc_file;
	int			p_r; // pipe read
	int			p_wr; // pipe write
	pid_t		kill_pid;
	char		**test;
}	t_shell;

//unset.c
void		ft_unset(t_shell *sh);
//ft_export.c
void		ft_export(t_shell *sh);
//cd.c
static void	too_many_arg(t_shell *shell);
void		ms_cmd_execute_cd(t_shell *shell);
//pipe.c
// echo.c
void		ft_echo(t_shell *s);
void		ms_cmd_execute_pipe(t_shell *shell);
//signals.c
void		ms_signals_handler(t_shell *shell, int type, pid_t pid);
// mainc.c
void		ft_get_status_string(t_shell *shell);
void		msshell_do(t_shell *sh);
//utils.c
char		*ft_strcpy(char *dst, const char *src);
size_t		ft_strlen(const char *s);
void		*ft_memjoin(void *dst, const void *src);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		ft_putstr(char *str, int std_var);
void		ft_puterror(t_shell *shell, int code, char *name);
void		ms_cmd_argv_free(t_tok *cmd);
void		ms_shell_destroy(t_shell *shell);
void		ms_cmd_execute_command_error(t_shell *shell, int tempfd_stdout);
//buildins.c
void		exec_buildin(t_shell *shell, char *cwd);
void		ms_cmd_execute_exit(t_shell *shell);
void		do_shell_command(t_shell *shell);
void		ms_cmd_execute_fork(t_shell *shell);
// redirects
void		fd_redirect_out(t_shell *shell);
void		fd_redirect_in(t_shell *shell);
void		ms_write_heredoc_file_readline(t_shell *shell);
void		ms_create_heredoc_file(t_shell *shell);
char		**ft_split(char const *s, char c);
void		find_spec(t_tok **tokens);
t_list		*list_of_bildins(void);
void		parse_of_line(t_tok **tokens);
int			check_void_pipe(char **arr);
t_list		*create_node(void *data, int num_type);
void		del_list(t_list **list);
t_tok		*parse(char *line, char *env[], int *flag, int *status);
void		check_env(char **line, char **env);
t_tok		*create_token_list(char **arr, int total, char **env);
void		add_node(t_list **list, t_list *new);
t_redir		*init_red(void);
char		*del_quots(char *line, char **env);
void		count_quots(int *q, int *dub_q, char *line);
int			check_flag(char c, int flag);
char		*add_part_arr(char *line, int i, int j);
char		**mini_split(int total, const char *line, int i, char del);
int			count_del(char *line, char del);
void		rec_cmd(t_tok **toks, int *i);
int			check_cmd_build_in(t_tok *tok);
void		count_redir(int *i, char c, t_tok **tmp);
void		sort_of_redir(t_tok **toks, int type, char *buf);
void		new_redir(t_tok **toks, int type, int *i, int *flag);
char		*change_var(char *line, int *i, char **env);
char		**array_2d_dup(char **array);
size_t		len_2d_array(char **string);
int			skip_quots(char *line, char *sym, int i);
void		do_shell_command(t_shell *shell);
int			build_or_cmds(t_shell *shell);
void		ft_is_dir(t_shell *shell, char *name);
void		ms_write_heredoc_file(t_shell *shell);
char		parse_cmd(char **dst, const char *cmd, char *path);
struct env1	*env_list(char **env);
void		free_env(t_env *env);

#endif
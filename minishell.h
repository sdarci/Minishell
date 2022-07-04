/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 20:41:44 by eheike            #+#    #+#             */
/*   Updated: 2022/06/30 20:41:47 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define NAME "MINISHELL:"

int	g_lobal_status;

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
	char			*in;
	char			*out;
	int				type_in;
	int				type_out;
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
	t_redir			*red;
	t_list			*check;
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
	int			p_r;
	int			p_wr;
	pid_t		kill_pid;
	char		**test;
	bool		stdin_pipe;
	bool		stdout_pipe;
}	t_shell;

void		ft_unset(t_shell *sh);
void		ft_export(t_shell *sh);
void		ms_cmd_execute_cd(t_shell *shell);
// echo.c
void		ft_echo(t_shell *s);
void		ms_cmd_execute_pipe(t_shell *shell);
//signals.c
void		ms_signals_handler(t_shell *shell, int type, pid_t pid);
// mainc.c
void		ft_get_status_string(t_shell *shell, int flg);
void		msshell_do(t_shell *sh);
//utils.c
char		*ft_strcpy(char *dst, const char *src);
size_t		ft_strlen(const char *s);
void		*ft_memjoin(void *dst, const void *src);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		ft_putstr(char *str, int std_var);
int			ft_puterror(t_shell *shell, int code, char *name);
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
t_list		*list_of_bildins(void);
t_list		*create_node(void *data, int num_type);
void		add_node(t_list **list, t_list *new);
void		del_list(t_list **list);
t_tok		*parse(char *line, char *env[], int *flag, int *status);
t_tok		*lexer(char *line, int i, char **env, int total_pipes);
int			valid_check(char *line, int *flag, int *status);
int			check_void_pipe(char **arr);
int			parse_of_line(t_tok **tokens);
void		check_env(char **line, char **env);
t_tok		*create_token_list(char **arr, int total, char **env);
t_redir		*init_red(void);
char		*del_quots(char *line, char **env);
int			count_quots(int *q, int *dub_q, char *line);
char		**mini_split(int total, const char *line, char del);
int			count_del(char *line, char del);
int			find_spec(t_tok **tokens);
int			rec_cmd(t_tok **toks, int *i);
int			count_redir(int *i, char c, t_tok **tmp);
int			new_redir(t_tok **toks, int type, int *i, int *flag);
char		*change_var(char *line, int *i, char **env, int flg);
char		*repl_line(char *line, int start, char *val, int *len);
char		**array_2d_dup(char **array);
size_t		len_2d_array(char **string);
int			skip_quots(char *line, char *sym, int i);
int			one_skip_q(char *line, int i);
void		parse_error(t_tok **tok, char *str, int status);
void		do_shell_command(t_shell *shell);
int			build_or_cmds(t_shell *shell);
void		ft_is_dir(t_shell *shell, char *name);
void		ms_write_heredoc_file(t_shell *shell);
char		parse_cmd(char **dst, const char *cmd, char *path);
struct env1	*env_list(char **env);
void		free_env(t_env *env);
void		ft_pwd(t_shell *sh);
void		ms_signal_handler(int sigtype);
t_shell		*for_norma(t_shell *s, char **argv, int argc, char **env);
void		free_red(t_tok	*tmp);
void		free_check(t_tok *tmp);
void		freee(t_tok *tmp);
void		error_func1(t_shell *shell);
void		func_vivod(t_shell *sh, int i, int j);
void		check_kostl(t_shell *shell, char *filename);
t_shell		*struct_init(void);
char		**rec_arr(char **arr, char *filename);
#endif
#include "minishell.h"

static void	ms_write_heredoc_file(t_shell *shell)
{
	if (shell->cmd->red != NULL)
	{
		if (shell->cmd->red->type_in == 4)
		{
			ms_write_heredoc_file_readline(shell);
			//shell->cmd->red->out = shell->heredoc_file;
		}
	}
}


static int	build_or_cmds(t_shell *shell)
{
	// if (ft_strcmp(shell->cmd->cmd_arr[0], "cd") == 0)
	// 	ms_cmd_execute_cd(shell);
	// else if (ft_strcmp(shell->cmd->cmd_arr[0], "prompt") == 0)
	// 	ms_cmd_execute_prompt(shell);
	// else if (ft_strcmp(shell->cmd->cmd_arr[0], "pwd") == 0)
	// 	ms_cmd_execute_pwd(shell);
	// else if (ft_strcmp(shell->cmd->cmd_arr[0], "test") == 0)
	// 	ms_cmd_execute_test(shell);
	if (ft_strcmp(shell->cmd->cmd_arr[0], "exit") == 0)
		ms_cmd_execute_exit(shell);
	else if (ft_strcmp(shell->cmd->cmd_arr[0], "echo") == 0)
		ft_echo(shell);
	// else if (ft_strcmp(shell->cmd->cmd_arr[0], "env") == 0)
	// 	ms_cmd_execute_env(shell);
	// else if (shell->cmd->cmd_arr[0][0])
	do_shell_command(shell);
	ms_cmd_argv_free(shell->cmd);
	ms_shell_destroy(shell);
	exit(0);
}

static void	ft_is_dir(t_shell *shell, char *name)
{
	int	fd;

	fd = open(name, O_WRONLY);
	if (fd < 0 && errno == 21)
	{
		ft_putstr(name, 2);
		ft_putstr(" - is a directory\n", 2);
		ms_cmd_argv_free(shell->cmd);
		ms_shell_destroy(shell);
		exit(126);
	}
	else if (fd > 0)
		close(fd);
}

static char	*check_cmd(const char *cmd, size_t s_cmd, char *path, size_t s_path)
{
	char	*new;
	size_t	i;
	int		flg;

	flg = s_path != 0;
	i = -1;
	new = malloc(sizeof(char) * (s_cmd + s_path + 1 + flg));
	if (!new)
		return (NULL);
	while (++i < s_path)
		new[i] = path[i];
	if (flg)
		new[s_path] = '/';
	i = -1;
	while (++i < s_cmd)
		new[i + s_path + flg] = cmd[i];
	new[i + s_path + flg] = 0;
	if (!access(new, X_OK))
		return (new);
	free(new);
	return (NULL);
}

static char	parse_cmd(char **dst, const char *cmd, char *path)
{
	size_t		size_cmd;
	size_t		size_path;
	static char	*tmp;

	size_cmd = 0;
	if (!tmp)
		tmp = *dst;
	while (cmd[size_cmd])
		size_cmd++;
	*dst = check_cmd(cmd, size_cmd, path, 0);
	if (*dst)
		return (0);
	while (*path)
	{
		size_path = 0;
		while (path[size_path] && path[size_path] != ':')
			size_path++;
		*dst = check_cmd(cmd, size_cmd, path, size_path);
		if (*dst)
			return (0);
		path += size_path + (path[size_path] == ':');
	}
	*dst = tmp;
	return (1);
}

void	do_shell_command(t_shell *shell)
{
	size_t	i;
	char	*path;
	t_tok	*cmdexe;

	i = 0;
	cmdexe = shell->cmd;
	while (shell->copy_env[i] && ft_strncmp("PATH=", shell->copy_env[i], 5) != 0)
		i++;
	if (!shell->copy_env[i] || ft_strchr(shell->cmd->cmd_arr[0], '/'))
		path = "";
	else
		path = (shell->copy_env[i]) + 5;
	if (parse_cmd(&((shell->cmd->cmd_arr)[0]), (shell->cmd->cmd_arr)[0], path))
	{
		ft_putstr("Command doesn't exist(", 2);
		ft_putstr((shell->cmd->cmd_arr)[0], 2);
		ft_putstr(").\n", 2);
		ms_cmd_argv_free(shell->cmd);
		ms_shell_destroy(shell);
		exit(127);
	}
	ft_is_dir(shell, shell->cmd->cmd_arr[0]);
	execve(shell->cmd->cmd_arr[0],shell->cmd->cmd_arr, shell->copy_env);
	ft_puterror(shell, 3, strerror(errno));
}


void	ms_cmd_execute_fork(t_shell *shell)
{
	pid_t	pid;
	int		tempfd_stdout;
	int		test;
	
	ms_create_heredoc_file(shell);
	pid = fork();
	if (pid < 0)
		printf("ERROR BLA BLA BLA \n");
	if (pid == 0)
	{
		//ms_signals_handler(shell, 1, 0);
		tempfd_stdout = dup(1);
		//ms_cmd_execute_fd_null(shell);
		if (shell->p_r)
		{
			dup2(shell->p_r, 0);
		}
		if (shell->p_wr)
		{
			dup2(shell->p_wr, 1);
		}
		ms_write_heredoc_file(shell);
		fd_redirect_in(shell);
		fd_redirect_out(shell);
		build_or_cmds(shell);
		ms_cmd_execute_command_error(shell, tempfd_stdout);
	}
	else
		waitpid(pid, &test, WUNTRACED);
	//ms_signals_handler(shell, 2, pid);
	//build_or_cmds(shell);
	//ms_cmd_execute_after_fork(shell, pid);
}

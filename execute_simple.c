/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:56:44 by sdarci            #+#    #+#             */
/*   Updated: 2022/06/30 22:01:15 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_write_heredoc_file(t_shell *shell)
{
	if (shell->cmd->red != NULL)
	{
		if (shell->cmd->red->type_in == 4)
			ms_write_heredoc_file_readline(shell);
	}
}

int	build_or_cmds(t_shell *shell)
{
	if (shell->cmd->cmd_arr == NULL)
		exit(127);
	if (ft_strcmp(shell->cmd->cmd_arr[0], "cd") == 0)
		ms_cmd_execute_cd(shell);
	if (ft_strcmp(shell->cmd->cmd_arr[0], "exit") == 0)
		ms_cmd_execute_exit(shell);
	else if (ft_strcmp(shell->cmd->cmd_arr[0], "echo") == 0)
		ft_echo(shell);
	else if (ft_strcmp(shell->cmd->cmd_arr[0], "export") == 0)
		ft_export(shell);
	else if (ft_strcmp(shell->cmd->cmd_arr[0], "echo") == 0)
		ft_echo(shell);
	else if (ft_strcmp(shell->cmd->cmd_arr[0], "pwd") == 0)
		ft_pwd(shell);
	else if (shell->cmd->cmd_arr[0][0])
		do_shell_command(shell);
	ms_cmd_argv_free(shell->cmd);
	exit(127);
}

void	ft_is_dir(t_shell *shell, char *name)
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

char	parse_cmd(char **dst, const char *cmd, char *path)
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

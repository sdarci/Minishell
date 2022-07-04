/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <sdarci@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:09:30 by sdarci            #+#    #+#             */
/*   Updated: 2022/06/30 18:09:30 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_shell_command(t_shell *shell)
{
	size_t	i;
	char	*path;
	t_tok	*cmdexe;

	i = 0;
	if (shell->cmd == NULL)
		exit(1);
	cmdexe = shell->cmd;
	while (shell->copy_env[i] && \
	ft_strncmp("PATH=", shell->copy_env[i], 5) != 0)
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
		exit(127);
	}
	ft_is_dir(shell, shell->cmd->cmd_arr[0]);
	execve(shell->cmd->cmd_arr[0], shell->cmd->cmd_arr, shell->copy_env);
	ft_puterror(shell, 3, strerror(errno));
}

void	ms_cmd_execute_fork(t_shell *shell)
{
	pid_t	pid;
	int		tempfd_stdout;

	ms_create_heredoc_file(shell);
	pid = fork();
	if (pid < 0)
		printf("ERROR: cant create PID \n");
	if (pid == 0)
	{
		ms_signals_handler(shell, 2, 0);
		tempfd_stdout = dup(1);
		ms_write_heredoc_file(shell);
		fd_redirect_out(shell);
		fd_redirect_in(shell);
		if (shell->stdin_pipe)
			dup2(shell->p_r, 0);
		if (shell->stdout_pipe)
			dup2(shell->p_wr, 1);
		build_or_cmds(shell);
		ms_cmd_execute_command_error(shell, tempfd_stdout);
	}
	else
		ms_signals_handler(shell, 2, pid);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <sdarci@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:02:21 by sdarci            #+#    #+#             */
/*   Updated: 2022/06/30 18:29:47 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pre_executer(t_shell *shell, int fd_r, int fd_wr)
{
	if (shell->cmd->next == NULL)
	{
		shell->stdin_pipe = true;
		shell->stdout_pipe = false;
	}
	else
	{
		shell->stdin_pipe = fd_r;
		shell->stdout_pipe = fd_wr;
	}
}

void	ms_cmd_execute_pipe(t_shell *shell)
{
	int		fd[4];

	pipe(fd);
	fd[2] = fd[0];
	fd[3] = fd[1];
	shell->p_r = 0;
	shell->p_wr = fd[3];
	pre_executer(shell, false, true);
	ms_cmd_execute_fork(shell);
	while (shell->cmd->next != NULL)
	{
		close(fd[3]);
		pipe(fd);
		fd[3] = fd[1];
		shell->cmd = shell->cmd->next;
		pre_executer(shell, true, true);
		shell->p_r = fd[2];
		shell->p_wr = fd[1];
		ms_cmd_execute_fork(shell);
		close(fd[2]);
		fd[2] = fd[0];
	}
	fd[2] = fd[0];
	close(fd[3]);
	close(fd[2]);
}

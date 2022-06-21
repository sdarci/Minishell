#include "minishell.h"

void	pre_executer(t_shell *shell, int fd_r, int fd_wr)
{
	if (shell->cmd->next == NULL)
	{
		shell->p_r = fd_r;
		shell->p_wr = 1;
	}
	else
	{
		shell->p_r = fd_r;
		shell->p_wr = fd_wr;
	}
}


void	ms_cmd_execute_pipe(t_shell *shell)
{
	int		fd[4];

	pipe(fd);
	fd[2] = fd[0];
	fd[3] = fd[1];
	pre_executer(shell, 0, fd[1]);
	ms_cmd_execute_fork(shell);
	while (shell->cmd->next != NULL)
	{
		fd[2] = fd[0];
		fd[3] = fd[1];
		pipe(fd);
		shell->cmd = shell->cmd->next;
		pre_executer(shell, fd[2], fd[1]);
		ms_cmd_execute_fork(shell);
		close(fd[2]);
		close(fd[1]);
	}
	fd[2] = fd[0];
	close(fd[3]);
	close(fd[2]);
}
#include "minishell.h"

void	ms_cmd_execute_fd_redirect_out(t_shell *shell)
{
	int	fd;

	fd = 0;
	if (shell->cmd->red->type_out == 1 || shell->cmd->red->type_out == 2) 
	{
		printf("TEST\n");
		if (shell->cmd->red->type_out == 1)
			fd = open(shell->cmd->red->out,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (shell->cmd->red->type_out == 2)
			fd = open(shell->cmd->red->out,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			ft_putstr(COLOR_RED, 2);
			ft_putstr("Error with ", 2);
			if (shell->cmd->red->type_out == 1)
				perror(shell->cmd->red->out);
			if (shell->cmd->red->type_out == 2)
				perror(shell->cmd->red->out);
			ft_putstr(COLOR_RESET, 2);
			ms_cmd_argv_free(shell->cmd);
			//ms_shell_destroy(shell); error
			exit(1);
		}
		dup2(fd, 1);
		do_shell_command(shell);
	}
}
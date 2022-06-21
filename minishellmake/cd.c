#include "minishell.h"

static void	too_many_arg(t_shell *shell)
{
	shell->status = 1;
	ft_putstr("cd: neobhodimo ukazat tolko odin parametr\n", 2);
}

static void	error_chdir(t_shell *shell)
{
	shell->status = 1;
	ft_putstr("Error with ", 2);
	ft_putstr(shell->cmd->cmd_arr[0], 2);
	ft_putstr(": ", 2);
	ft_putstr(shell->cmd->cmd_arr[1], 2);
	ft_putstr(" ", 2);
	ft_putstr(strerror(errno), 2);
	write(2, "\n", 1);
}

void	ms_cmd_execute_cd(t_shell *shell)
{
	if (shell->cmd->cmd_arr[1] == NULL)
	{
		shell->status = 0;
		getenv("HOME");
		ft_get_status_string(shell);
	}
	else if (shell->cmd->cmd_arr[3] != NULL)
		too_many_arg(shell);
	else
	{
		if (chdir(shell->cmd->cmd_arr[1]) != 0)
			error_chdir(shell);
		else
		{
			//shell->status = 0;
			ft_get_status_string(shell);
		}
	}
}
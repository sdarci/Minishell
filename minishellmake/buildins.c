#include "minishell.h"

void	exec_buildin(t_shell *shell, char *cwd)
{
		if (!strcmp(shell->input, "pwd"))
			printf("%s\n", cwd); //pwd 
		if (strstr(shell->input, "echo"))
			ft_echo(shell);
		// if (strstr(shell->input, "env"))
		// 	env_list(shell->env1, shell->copy_env); env poto.
		if (strstr(shell->input, "clear"))
			printf ("\033[0d\033[2J");
		if (strstr(shell->input, "exit"))
			ms_cmd_execute_exit(shell);
}
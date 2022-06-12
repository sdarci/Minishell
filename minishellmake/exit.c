#include "minishell.h"

void	ms_cmd_execute_exit(t_shell *shell)
{
	(void)shell;
	printf("\033[0;31m");
	printf("Exit: Всем пока!!\n");
	printf("\033[0m");
	exit(0);
}
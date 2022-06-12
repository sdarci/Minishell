#include "minishell.h"

static void	too_many_arg(t_shell *shell)
{
	//shell->status = 1;
	printf("cd: too many args for cd\n");
}


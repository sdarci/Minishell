#include "minishell.h"

char	**ft_export_in_cpy(char **copy_env, char **cpy, char *cmd_arr)
{
	int		i;

	i = 0;
	while(copy_env[i] != NULL)
		i++; //29
	cpy = (char **)malloc(sizeof(char *) * (i + 2));
	int j = 0;
	while (j != i)
	{
		cpy[j] = copy_env[j];
		printf("+++++++++%s++++++++\n", cpy[j]);
		++j;
	}
	printf("%d\n", j);
	cpy[j] = cmd_arr;
	cpy[j+1] = NULL;
	i = 0;
	//free(copy_env);
	return (cpy);
}


void	ft_export(t_shell *sh)
{
	int	i;
	int test = 0;
	int test2=0;
	char **cpy;

	i = 0;
	if (sh->cmd->cmd_arr[1] == NULL)
	{
		while(sh->copy_env[i++] != NULL)
			printf("%s\n",sh->copy_env[i]);
		return ;
	}
		
	if (sh->cmd->cmd_arr[2] != NULL)
	{
		printf("ERROR \n");
		return ;
	}
		if (sh->cmd->cmd_arr[1] != NULL)
	{
		cpy = ft_export_in_cpy(sh->copy_env, cpy, sh->cmd->cmd_arr[1]);
		free(sh->copy_env);
		sh->copy_env = cpy;
	}
}
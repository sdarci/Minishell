#include "minishell.h"

int	find_variable(char **env, char *s)
{
	size_t	i;
	int		res;
	char	flg;

	i = 0;
	flg = 0;
	res = 0;
	while (s[i] && s[i] != '=' && s[i] != '+')
		i++;
	while (!flg && env[res])
	{
		while (env[res] && ft_strncmp(s, env[res], i))
			res++;
		if (env[res] && (env[res][i] == '=' || env[res][i] == '+'))
			flg = 1;
		else if (env[res])
			res++;
	}
	if (!env[res])
		return (-1);
	return (res);
}

static void	delete_variable(char **env)
{
	char	*tmp;
	size_t	i;

	tmp = *env;
	printf("%s\n", tmp);
	i = -1;
	while (env[++i])
		env[i] = env[i + 1];
}

void	ft_unset(t_shell *sh)
{
	int	i;
	int	j;

	sh->status = 0;
	i = 0;
	if (sh->cmd->cmd_arr[1] != NULL)
	{
		while (1)
		{
			j = find_variable(sh->copy_env, (sh->cmd->cmd_arr)[1]);
			if (j > 0)
				delete_variable(sh->copy_env + j);
			else
			{
				printf("ERROR NOTHINK TO UNSET\n");
				break ;
			}
		}
	}
	else
		printf("UNSET)\n");
}

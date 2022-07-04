/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exportt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:57:27 by sdarci            #+#    #+#             */
/*   Updated: 2022/06/30 20:41:20 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**memort(char **cpy, int i)
{
	cpy = (char **)malloc(sizeof(char *) * (i + 2));
	if (!cpy)
		exit (127);
	return (cpy);
}

char	**izmenit_peremennuyu(int f, char **env, char *str, int i)
{
	char	**cpy;

	cpy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!cpy)
		exit(127);
	free(env[f]);
	env[f] = NULL;
	env[f] = ft_strdup(str);
	i = -1;
	while (env[++i] != NULL)
		cpy[i] = env[i];
	cpy[i] = NULL;
	return (cpy);
}

int	ft_check_povtor(char *str_chk, char **mass)
{
	char	**spl;
	int		i;
	int		j;
	int		a;

	j = 0;
	i = -1;
	spl = ft_split(str_chk, '=');
	while (mass[++i] != NULL )
	{
		a = 0;
		while (mass[i][a] && mass[i][a] != '=')
			a++;
		if (ft_strncmp(spl[0], mass[i], a) == 0)
		{
			while (spl[j])
				free(spl[j++]);
			free(spl);
			return (i);
		}
	}
	while (spl[j])
		free(spl[j++]);
	free(spl);
	return (-1);
}

char	**ft_export_in_cpy(char **copy_env, char **cpy, char *cmd_arr)
{
	int		i;
	int		flag;
	int		j;

	i = 0;
	flag = ft_check_povtor(cmd_arr, copy_env);
	while (copy_env[i] != NULL)
		i++;
	if (flag == -1)
		cpy = memort(cpy, i);
	else
	{
		cpy = izmenit_peremennuyu(flag, copy_env, cmd_arr, i);
		return (cpy);
	}
	j = -1;
	while (++j != i)
		cpy[j] = copy_env[j];
	cpy[j] = ft_strdup(cmd_arr);
	cpy[j + 1] = NULL;
	i = 0;
	return (cpy);
}

void	ft_export(t_shell *sh)
{
	int		i;
	char	**cpy;
	int		j;

	cpy = NULL;
	i = -1;
	j = 0;
	if (sh->cmd->cmd_arr[1] == NULL)
	{
		func_vivod(sh, i, j);
		return ;
	}
	if (sh->cmd->cmd_arr[2] != NULL)
	{
		g_lobal_status = 1;
		printf("ERROR \n");
		return ;
	}
	if (sh->cmd->cmd_arr[1] != NULL)
	{
		cpy = ft_export_in_cpy(sh->copy_env, cpy, sh->cmd->cmd_arr[1]);
		free(sh->copy_env);
		sh->copy_env = cpy;
		g_lobal_status = 0;
	}
}

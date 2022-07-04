/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <sdarci@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:26:55 by sdarci            #+#    #+#             */
/*   Updated: 2022/06/30 17:27:05 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (env[res] && (env[res][i] == '=' || env[res][i] == '+' \
		|| env[res][i] == 0))
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
	free(tmp);
}

void	ft_unset(t_shell *sh)
{
	int	i;
	int	j;
	int	flg;

	i = 0;
	flg = 0;
	if (sh->cmd->cmd_arr[1] != NULL)
	{
		while (1)
		{
			j = find_variable(sh->copy_env, (sh->cmd->cmd_arr)[1]);
			if (j > 0)
			{
				delete_variable(sh->copy_env + j);
				flg = 1;
				break ;
			}
			if (flg == 0)
			{
				printf("ERROR NOTHINK TO UNSET\n");
				break ;
			}
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_norma2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:05:52 by sdarci            #+#    #+#             */
/*   Updated: 2022/06/30 21:59:56 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	func_vivod(t_shell *sh, int i, int j)
{
	int	flg;

	flg = 1;
	while (sh->copy_env[++i] != NULL)
	{
		write(1, "declare -x ", 12);
		while (sh->copy_env[i][j] != '\0')
		{
			write(1, &sh->copy_env[i][j], 1);
			if (sh->copy_env[i][j] == '=' && flg == 1)
			{
				write(1, "\"", 1);
				flg = 0;
			}
			j++;
		}
		flg = 1;
		j = 0;
		write(1, "\"", 1);
		write(1, "\n", 1);
	}
	g_lobal_status = 0;
	return ;
}

void	check_kostl(t_shell *shell, char *filename)
{
	if (shell->cmd->cmd_arr == NULL)
		return ;
	if (ft_strcmp(shell->cmd->cmd_arr[0], "cat") == 0 || \
	ft_strcmp(shell->cmd->cmd_arr[0], "wc") == 0 || \
	ft_strcmp(shell->cmd->cmd_arr[0], "grep") == 0)
		shell->cmd->cmd_arr = rec_arr(shell->cmd->cmd_arr, filename);
}

t_shell	*struct_init(void)
{
	t_shell	*s;

	s = (t_shell *)malloc(sizeof(t_shell));
	if (!s)
		return (NULL);
	s->input = NULL;
	s->prompt_line = NULL;
	s->line = NULL;
	s->heredoc_file = NULL;
	s->fd_her = -1;
	s->status = 0;
	s->env1 = (t_env *)malloc(sizeof(t_env));
	return (s);
}

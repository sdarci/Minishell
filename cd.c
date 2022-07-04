/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:06:56 by sdarci            #+#    #+#             */
/*   Updated: 2022/06/30 20:41:20 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_chdir(t_shell *shell)
{
	g_lobal_status = 1;
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
		g_lobal_status = 0;
		chdir(getenv("HOME"));
		return ;
	}
	if (shell->cmd->cmd_arr[2] != NULL)
	{
		g_lobal_status = 1;
		ft_putstr("cd: neobhodimo ukazat tolko odin parametr\n", 2);
	}
	else if (shell->cmd->cmd_arr[1] != NULL)
	{
		if (chdir(shell->cmd->cmd_arr[1]) == -1)
		{
			error_chdir(shell);
			return ;
		}
		else
		{
			g_lobal_status = 0;
			ft_get_status_string(shell, 1);
			return ;
		}
	}
}

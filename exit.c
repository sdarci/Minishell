/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:09:36 by sdarci            #+#    #+#             */
/*   Updated: 2022/07/01 14:26:39 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_cmd_execute_exit(t_shell *shell)
{
	if (shell->cmd == NULL || shell->cmd->cmd_arr[1] == NULL)
	{
		(void)shell;
		printf("\033[0;31m");
		printf("Exit: Всем пока!!\n");
		printf("\033[0m");
		exit(0);
	}
	else
	{
		g_lobal_status = 1;
		ft_putstr_fd("TOO MANY ARGS FOR EXIT\n", 2);
		return ;
	}
}

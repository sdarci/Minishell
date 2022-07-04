/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:52:57 by sdarci            #+#    #+#             */
/*   Updated: 2022/06/30 20:41:20 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	with_n(int i, t_shell *s)
{
	i = 2;
	while (s->cmd->cmd_arr[i] != NULL \
	&& ft_strcmp(s->cmd->cmd_arr[i], "-n") == 0)
		i++;
	while (s->cmd->cmd_arr[i] != NULL)
	{
		write(1, s->cmd->cmd_arr[i], ft_strlen(s->cmd->cmd_arr[i]));
		write(1, " ", 1);
		i++;
	}
}

void	ft_echo(t_shell *s)
{
	int		i;

	g_lobal_status = 0;
	i = 0;
	if (s->cmd->cmd_arr[1] == NULL)
	{
		while (s->input[i] != '\0')
			i++;
		write(1, s->input + 5, i - 5);
		write(1, "\n", 1);
	}
	else if (ft_strcmp(s->cmd->cmd_arr[1], "-n") != 0)
	{
		while (s->cmd->cmd_arr[i + 1] != NULL)
		{
			i++;
			write(1, s->cmd->cmd_arr[i], ft_strlen(s->cmd->cmd_arr[i]));
			write(1, "\n", 1);
		}
	}
	else if (ft_strcmp(s->cmd->cmd_arr[1], "-n") == 0)
		with_n(i, s);
}

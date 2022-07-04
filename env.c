/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:08:58 by sdarci            #+#    #+#             */
/*   Updated: 2022/06/30 20:41:20 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_shell *sh)
{
	int	i;

	i = -1;
	if (sh->cmd->cmd_arr[1] == NULL)
	{
		g_lobal_status = 0;
		while (sh->copy_env[++i] != NULL)
			printf("%s\n", sh->copy_env[i]);
	}
	else
		g_lobal_status = 1;
}

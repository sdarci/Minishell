/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:26:13 by sdarci            #+#    #+#             */
/*   Updated: 2022/06/30 20:41:20 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_shell *sh)
{
	char	cwd[999];

	g_lobal_status = 0;
	sh->cmd->flag_dub_q = 1;
	if (getcwd(cwd, 999))
	{
		ft_putstr(cwd, 1);
		ft_putstr("\n", 1);
	}
	else
	{
		g_lobal_status = 1;
		ft_putstr(COLOR_RED, 2);
		perror("Error with getcwd()");
		ft_putstr(COLOR_RESET, 2);
	}
}

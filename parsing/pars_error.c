/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 19:27:43 by eheike            #+#    #+#             */
/*   Updated: 2022/06/30 20:41:20 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_error(t_tok **tok, char *str, int status)
{
	g_lobal_status = status;
	if (tok != NULL)
		ms_cmd_argv_free(*tok);
	if (status == 1)
		ft_putstr_fd("Malloc error\n", 2);
	if (status == 100)
		ft_putstr_fd("Quotes are not closed\n", 2);
	if (status == 258)
	{
		ft_putstr_fd("Syntax error near unexpected token '", 2);
		ft_putstr_fd(str, 2);
		ft_putchar_fd(39, 2);
		ft_putchar_fd('\n', 2);
	}
}

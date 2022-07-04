/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_sym.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 20:15:34 by eheike            #+#    #+#             */
/*   Updated: 2022/06/29 19:26:15 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	find_red(char c, t_tok **tmp, int *i)
{
	if (c == '>' || c == '<')
	{
		if (count_redir(i, c, tmp) == 1)
			return (1);
		(*i)--;
	}
	return (0);
}

int	find_spec(t_tok **tokens)
{
	int		i;
	t_tok	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		i = 0;
		while (tmp->line[i])
		{
			i = one_skip_q(tmp->line, i);
			if (find_red(tmp->line[i], &tmp, &i) == 1)
			{
				parse_error(tokens, NULL, 1);
				return (1);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

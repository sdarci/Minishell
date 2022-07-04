/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quots2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:09:21 by eheike            #+#    #+#             */
/*   Updated: 2022/06/28 19:21:00 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	incr_q(char c, int *flag, char *line, int i)
{
	(*flag)++;
	i++;
	while (line[i] && line[i] != c)
		i++;
	if (line[i] == c)
		(*flag)++;
	return (i);
}

int	count_quots(int *q, int *dub_q, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] != 34 && line[i] != 39)
			i++;
		if (!line[i])
			return (0);
		else if (line[i] == 34)
			i = incr_q(line[i], dub_q, line, i);
		else if (line[i] == 39)
			i = incr_q(line[i], q, line, i);
		i++;
	}
	if (*dub_q % 2 || *q % 2)
		return (1);
	return (0);
}

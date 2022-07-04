/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:19:27 by eheike            #+#    #+#             */
/*   Updated: 2022/06/28 19:08:49 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cmd_join(t_tok **toks, int *i, int j, int fl)
{
	char	*tmp;
	char	*buf;

	buf = NULL;
	if (fl == 1)
		buf = ft_substr((*toks)->line, j, (*i) - j + 1);
	else
		buf = ft_substr((*toks)->line, j, (*i) - j);
	if (buf == NULL)
		return (1);
	if ((*toks)->cmd == NULL)
		(*toks)->cmd = buf;
	else
	{
		tmp = (*toks)->cmd;
		(*toks)->cmd = ft_strjoin((*toks)->cmd, buf);
		free(tmp);
		free(buf);
		if ((*toks)->cmd == NULL)
			return (1);
	}
	return (0);
}

static void	count_in_quots(char c, int *i, char *line)
{
	(*i)++;
	while (line[*i] != c)
		(*i)++;
}

int	rec_cmd(t_tok **toks, int *i)
{
	int		j;

	while ((*toks)->line[*i] && (*toks)->line[*i] != '>' && \
	(*toks)->line[*i] != '<')
	{
		j = (*i);
		if ((*toks)->line[*i] == 34 || (*toks)->line[*i] == 39)
		{
			count_in_quots((*toks)->line[*i], i, (*toks)->line);
			if (cmd_join(toks, i, j, 1) == 1)
				return (1);
			if ((*toks)->line[*i])
				(*i)++;
		}
		else
		{
			while ((*toks)->line[*i] && (*toks)->line[*i] != '>' \
			&& (*toks)->line[*i] != '<' && (*toks)->line[*i] != 34 \
			&& (*toks)->line[*i] != 39)
				(*i)++;
			if (cmd_join(toks, i, j, 0) == 1)
				return (1);
		}
	}
	return (0);
}

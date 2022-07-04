/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:15:41 by eheike            #+#    #+#             */
/*   Updated: 2022/06/30 18:57:25 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_init_red(t_tok **tmp, int *flag, int *flag_dub)
{
	if ((flag || flag_dub) && (*tmp)->red == NULL)
	{
		(*tmp)->red = init_red();
		if ((*tmp)->red == NULL)
			return (1);
	}
	return (0);
}

int	count_redir(int *i, char c, t_tok **tmp)
{
	int	*flag;
	int	*flag_dub;

	flag = &(*tmp)->flag_l;
	flag_dub = &(*tmp)->flag_dub_l;
	if (c == '>')
	{
		flag = &(*tmp)->flag_r;
		flag_dub = &(*tmp)->flag_dub_r;
	}
	if ((*tmp)->line[*i + 1] != c)
		(*flag)++;
	else
	{
		(*flag_dub)++;
		(*i)++;
	}
	(*i)++;
	while ((*tmp)->line[*i] == 32)
		(*i)++;
	if (check_init_red(tmp, flag, flag_dub) == 1)
		return (1);
	return (0);
}

static int	sort_of_redir(t_tok **toks, int type, char *buf)
{
	t_list	*red;

	if ((type == 1 || type == 2) && \
	((*toks)->flag_r + (*toks)->flag_dub_r == 1))
	{
		(*toks)->red->out = buf;
		(*toks)->red->type_out = type;
	}
	else if ((type == 3 || type == 4) && \
	((*toks)->flag_l + (*toks)->flag_dub_l == 1))
	{
		(*toks)->red->in = buf;
		(*toks)->red->type_in = type;
	}
	else if ((type == 3 || type == 4) && \
	((*toks)->flag_l + (*toks)->flag_dub_l != 1))
	{
		red = create_node(buf, type);
		if (red == NULL)
			return (1);
		add_node(&(*toks)->check, red);
	}
	else
		free(buf);
	return (0);
}

int	skip_quots(char *line, char *sym, int i)
{
	char	c;

	while (line[i] && ft_strchr(sym, line[i]) == 0)
	{
		if (line[i] == 34 || line[i] == 39)
		{
			c = line[i];
			i++;
			while (line[i] != c)
				i++;
		}
		i++;
	}
	return (i);
}

int	new_redir(t_tok **toks, int type, int *i, int *flag)
{
	int		j;
	char	*buf;

	if (type == 1 || type == 3)
		(*i)++;
	else if (type == 2 || type == 4)
		(*i) += 2;
	while ((*toks)->line[*i] == ' ')
		(*i)++;
	j = *i;
	(*i) = skip_quots((*toks)->line, " ><", *i);
	if (j == (*i))
		return (258);
	buf = ft_substr((*toks)->line, j, *i - j);
	if (buf == NULL)
		return (1);
	buf = del_quots(buf, (*toks)->env);
	if (buf == NULL)
		return (1);
	if (sort_of_redir(toks, type, buf) == 1)
		return (1);
	(*flag)--;
	return (0);
}

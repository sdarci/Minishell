/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:15:41 by eheike            #+#    #+#             */
/*   Updated: 2022/06/20 18:53:59 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	count_redir(int *i, char c, t_tok **tmp)
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
	while ((*tmp)->line[*i] == ' ')
		(*i)++;
	if ((flag || flag_dub) && (*tmp)->red == NULL)
		(*tmp)->red = init_red();
	return ;
}

void	sort_of_redir(t_tok **toks, int type, char *buf)
{
	t_list	*red;
	
	if ((type == 1 || type == 2) && ((*toks)->flag_r + (*toks)->flag_dub_r == 1))
	{
		(*toks)->red->out = buf;
		(*toks)->red->type_out = type;
	}
	else if ((type == 1 || type == 2) && ((*toks)->flag_r + (*toks)->flag_dub_r != 1))
	{
		red = create_node(buf, type);
		add_node(&(*toks)->create, red);
	}
	else if ((type == 3 || type == 4) && ((*toks)->flag_l + (*toks)->flag_dub_l == 1))
	{
		(*toks)->red->in = buf;
		(*toks)->red->type_in = type;
	}
	else if ((type == 3 || type == 4) && ((*toks)->flag_l + (*toks)->flag_dub_l != 1))
	{
		red = create_node(buf, type);
		add_node(&(*toks)->check, red);
	}
	return ;
}

void	new_redir(t_tok **toks, int type, int *i, int *flag) // учесть кавычки
{
	int		j;
	int		a;
	char	*buf;
	char	c;

	if (type == 1 || type == 3)
		(*i)++;
	else if (type == 2 || type == 4)
		(*i) += 2;
	if ((*toks)->line[*i] == ' ')
		(*i)++;
	j = *i;
	while ((*toks)->line[*i] && (*toks)->line[*i] != ' ' && (*toks)->line[*i] != '>' && (*toks)->line[*i] != '<')
	{
		if ((*toks)->line[*i] == 34 || (*toks)->line[*i] == 39)
		{
			c = (*toks)->line[*i];
			(*i)++;
			while ((*toks)->line[*i] != c)
				(*i)++;
		}
		(*i)++;
	}
	buf = (char *)malloc(sizeof(char) * (*i - j + 1));
	if (buf == NULL)
		exit(1);// вернуть ошибку
	a = 0;
	while (j < *i)
		buf[a++] = (*toks)->line[j++];
	buf[a] = '\0';
	buf = del_quots(buf, (*toks)->env);
	sort_of_redir(toks, type, buf);
	(*flag)--;
	return ;
}
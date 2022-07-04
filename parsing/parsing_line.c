/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:50:17 by eheike            #+#    #+#             */
/*   Updated: 2022/06/30 21:56:59 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	change_arr_line(t_tok *tok)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tok->cmd_arr[i])
	{
		tmp = tok->cmd_arr[i];
		tok->cmd_arr[i] = ft_strtrim(tok->cmd_arr[i], ISSPACE);
		free(tmp);
		if (tok->cmd_arr[i] == NULL)
			return (1);
		tok->cmd_arr[i] = del_quots(tok->cmd_arr[i], tok->env);
		if (tok->cmd_arr[i] == NULL)
			return (1);
		i++;
	}
	return (0);
}

static int	choose_red(t_tok *tok, int *i)
{
	int	a;

	a = -1;
	if (tok->line[*i] == '>' && tok->line[(*i) + 1] != '>')
		a = new_redir(&tok, 1, i, &(tok->flag_r));
	else if (tok->line[*i] == '>' && tok->line[(*i) + 1] == '>')
		a = new_redir(&tok, 2, i, &(tok->flag_dub_r));
	else if (tok->line[*i] == '<' && tok->line[(*i) + 1] != '<')
		a = new_redir(&tok, 3, i, &(tok->flag_l));
	else if (tok->line[*i] == '<' && tok->line[(*i) + 1] == '<')
		a = new_redir(&tok, 4, i, &(tok->flag_dub_l));
	if (a != 0)
		return (a);
	return (0);
}

static int	cmd_and_red(t_tok *tmp, int *i)
{
	int	res;

	res = 0;
	if (rec_cmd(&tmp, i) == 1)
		return (1);
	while (tmp->flag_r || tmp->flag_dub_r || tmp->flag_l || tmp->flag_dub_l)
	{
		if (rec_cmd(&tmp, i) == 1)
			return (1);
		res = choose_red(tmp, i);
		if (res != 0)
			return (res);
		if (rec_cmd(&tmp, i) == 1)
			return (1);
	}
	tmp->cmd_arr = mini_split(count_del(tmp->cmd, ' '), tmp->cmd, ' ');
	if (tmp->cmd_arr == NULL && tmp->red == NULL)
	{
		return (1);
	}
	return (0);
}

int	parse_of_line(t_tok **tokens)
{
	int		i;
	int		res;
	t_tok	*tmp;

	tmp = *tokens;
	if (find_spec(tokens) == 1)
		return (1);
	while (tmp)
	{
		i = 0;
		res = cmd_and_red(tmp, &i);
		if (res != 0)
			return (res);
		if (tmp->cmd_arr)
		{
			res = change_arr_line(tmp);
			if (res == 1)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

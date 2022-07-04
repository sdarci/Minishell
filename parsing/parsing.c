/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:27:21 by eheike            #+#    #+#             */
/*   Updated: 2022/06/30 17:29:27 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_last_sym(char *line, int i)
{
	i--;
	while (i >= 0 && line[i] == 32)
		i--;
	if (line[i] == '|' || (line[i] == '>' && i > 0 && line[i - 1] != '>') || \
	(line[i] == '<' && i > 0 && line[i - 1] != '<'))
	{
		parse_error(NULL, &line[i], 258);
		return (1);
	}
	else if (line[i] == '>' && i > 0 && line[i - 1] == '>')
	{
		parse_error(NULL, ">>", 258);
		return (1);
	}
	else if (line[i] == '<' && i > 0 && line[i - 1] == '<')
	{
		parse_error(NULL, "<<", 258);
		return (1);
	}
	return (0);
}

static int	parse2(char *line, int *tot_p, int *i)
{
	if (*i == -1)
		return (1);
	else if (*i == -100)
	{
		parse_error(NULL, NULL, 100);
		return (1);
	}
	else if (*i == -258)
	{
		parse_error(NULL, "|", 258);
		return (1);
	}
	while (line[*i])
	{
		(*i) = one_skip_q(line, *i);
		if (line[*i] == '|')
			(*tot_p)++;
		if (line[*i] == '|' && line[*i - 1] == '|')
		{
			parse_error(NULL, "|", 258);
			return (1);
		}
		(*i)++;
	}
	return (0);
}

t_tok	*parse(char *line, char *env[], int *flag, int *status)
{
	int		i;
	int		res;
	int		total_pipes;
	t_tok	*tokens;

	total_pipes = 0;
	i = valid_check(line, flag, status);
	if (parse2(line, &total_pipes, &i) == 1)
		return (NULL);
	if (check_last_sym(line, i) == 1)
		return (NULL);
	tokens = lexer(line, i, env, total_pipes);
	if (tokens == NULL)
		return (NULL);
	res = parse_of_line(&tokens);
	if (res != 0)
	{
		parse_error(&tokens, "redirect", res);
		return (NULL);
	}
	return (tokens);
}

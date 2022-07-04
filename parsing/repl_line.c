/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:55:57 by eheike            #+#    #+#             */
/*   Updated: 2022/06/28 19:56:30 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*rec_line_with_value(char *res, char *val)
{
	char	*buf;
	char	*tmp;

	buf = ft_strdup(val);
	if (buf == NULL)
		return (NULL);
	tmp = res;
	res = ft_strjoin(res, buf);
	free(tmp);
	free(buf);
	if (res == NULL)
		return (NULL);
	return (res);
}

char	*repl_line(char *line, int start, char *val, int *len)
{
	char	*buf;
	char	*res;
	char	*tmp;

	if (line == NULL)
		return (NULL);
	res = ft_substr(line, 0, start - 1);
	if (val != NULL)
		res = rec_line_with_value(res, val);
	buf = ft_substr(line, *len, ft_strlen(line) + (*len));
	tmp = res;
	res = ft_strjoin(res, buf);
	free(tmp);
	free(buf);
	if (res == NULL)
		return (NULL);
	if (val != NULL)
		(*len) = start + ft_strlen(val) - ((*len) - start);
	else
		(*len) = start - 1;
	return (res);
}

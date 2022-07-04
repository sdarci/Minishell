/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quots.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:20:58 by eheike            #+#    #+#             */
/*   Updated: 2022/06/30 21:00:40 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	case_quots(char c, char **line, int i, char **env)
{
	i++;
	if (c == 34)
	{
		while ((*line)[i] != c)
		{
			while ((*line)[i] != '$' && (*line)[i] != c)
				i++;
			if ((*line)[i] == '$')
				(*line) = change_var(*line, &i, env, 0);
			if (*line == NULL)
				return (-1);
		}
	}
	else if (c == 39)
	{
		while ((*line)[i] != c)
			i++;
	}
	return (i);
}

static char	*line_join(char *buf, char *tmp)
{
	char	*tmp2;

	if (buf == NULL)
		buf = tmp;
	else
	{
		tmp2 = buf;
		buf = ft_strjoin(buf, tmp);
		free(tmp);
		free(tmp2);
		if (buf == NULL)
			return (NULL);
	}
	return (buf);
}

static char	*rewrite_without_q(char *line, int start, int end, int *i)
{
	char	*buf;
	char	*tmp;

	buf = NULL;
	if (start > 0)
		buf = ft_substr(line, 0, start);
	if (end > start + 1)
	{
		tmp = ft_substr(line, start + 1, end - start - 1);
		buf = line_join(buf, tmp);
	}
	if ((int)ft_strlen(line) > end + 1)
	{
		tmp = ft_substr(line, end + 1, ft_strlen(line) - end - 1);
		buf = line_join(buf, tmp);
	}
	if (buf == NULL)
	{
		buf = malloc(sizeof(char) * 1);
		buf[0] = '\0';
	}
	(*i) = (*i) - 2;
	free(line);
	return (buf);
}

static int	del_quots2(char **line, char **env, int i, int flag)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	if ((*line)[i] == 34 || (*line)[i] == 39)
	{
		flag = 1;
		start = i;
		i = case_quots((*line)[i], line, i, env);
		if (i == -1)
			return (-10);
		end = i;
	}
	else if ((*line)[i] == '$')
	{
		(*line) = change_var((*line), &i, env, 1);
		if ((*line) == NULL)
			return (-10);
	}
	if (flag == 1)
		(*line) = rewrite_without_q((*line), start, end, &i);
	return (i);
}

char	*del_quots(char *line, char **env)
{
	int		i;
	int		flag;

	i = 0;
	while (line[i] && line[i] != 34 && line[i] != 39 && line[i] != '$')
		i++;
	if (!line[i])
		return (line);
	while (line[i])
	{
		flag = 0;
		i = del_quots2(&line, env, i, flag);
		if (i == -10)
			return (NULL);
		if (i >= 0)
		{
			if (line[i])
				i++;
		}
		else
			i++;
	}
	return (line);
}

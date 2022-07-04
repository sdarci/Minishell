/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:23:51 by eheike            #+#    #+#             */
/*   Updated: 2022/06/30 21:52:21 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_flag(char c, int flag)
{
	if (c == 34 && flag == 0)
		return (1);
	else if (c == 39 && flag == 0)
		return (2);
	if (c == 34 && flag == 1)
		return (0);
	else if (c == 39 && flag == 2)
		return (0);
	else
		return (flag);
}

static char	**rec_line_of_split(const char *line, char del, int i, char **arr)
{
	int	e;
	int	flag;
	int	j;

	e = 0;
	while (line[i])
	{
		j = i;
		flag = 0;
		while (line[i] && !(line[i] == del && line[i + 1] != del && flag == 0))
		{
			flag = check_flag(line[i], flag);
			i++;
		}
		arr[e] = ft_substr(line, j, i - j);
		if (arr[e] == NULL)
			return (NULL);
		e++;
		if (line[i])
			i++;
	}
	arr[e] = NULL;
	return (arr);
}

char	**mini_split(int total, const char *line, char del)
{
	char	**arr;
	int		i;

	if (line == NULL)
		return (NULL);
	i = 0;
	arr = (char **)malloc(sizeof(char *) * (total + 2));
	if (arr == NULL)
		return (NULL);
	while (line[i] == 32)
		i++;
	arr = rec_line_of_split(line, del, i, arr);
	if (arr == NULL)
		return (NULL);
	return (arr);
}

int	one_skip_q(char *line, int i)
{
	char	c;

	if (line[i] == 34 || line[i] == 39)
	{
		c = line[i];
		i++;
		while (line[i] != c)
			i++;
	}
	return (i);
}

int	count_del(char *line, char del)
{
	int		i;
	int		total;

	i = 0;
	total = 0;
	if (line == NULL)
		return (0);
	while (line[i] == 32)
		i++;
	i = 0;
	while (line[i])
	{
		i = one_skip_q(line, i);
		if (line[i] == del && line[i + 1] != del)
			total++;
		i++;
	}
	if (line[i - 1] == del)
		total--;
	return (total);
}

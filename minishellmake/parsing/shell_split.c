/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:23:51 by eheike            #+#    #+#             */
/*   Updated: 2022/06/23 17:57:20 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_flag(char c, int flag)
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

char	*add_part_arr(char *line, int i, int j)
{
	char	*arr_part;

	arr_part = ft_substr(line, j, i - j);
	return (arr_part);
}

char	**mini_split(int total, const char *line, int i, char del)
{
	char	**arr;
	int		j;
	int		e;
	int		flag;

	if (line == NULL)
		return (NULL);
	i = 0;
	flag = 0;
	e = 0;
	arr = (char **)malloc(sizeof(char *) * (total + 2));
	if (arr == NULL)
		return (NULL); // проблема с маллок
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

int	count_del(char *line, char del)
{
	int		i;
	int		total;
	char	c;

	i = 0;
	total = 0;
	if (line == NULL)
		return (0);
	while (line[i])
		i++;
	i = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39) // есть такой же код, заменить на функцию
		{
			c = line[i];
			i++;
			while (line[i] != c)
				i++;
		}
		if (line[i] == del && line[i + 1] != del)
			total++;
		i++;
	}
	if (line[i - 1] == del)
		total--;
	return (total);
}
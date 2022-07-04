/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 19:34:19 by eheike            #+#    #+#             */
/*   Updated: 2022/06/29 19:41:47 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_void_pipe(char **arr)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (arr[i])
	{
		j = 0;
		flag = 0;
		while (arr[i][j])
		{
			if (arr[i][j] == ' ')
				flag++;
			j++;
		}
		if (flag == j)
			return (1);
		i++;
	}
	return (0);
}

static int	check_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != 32)
			return (0);
		i++;
	}
	return (1);
}

int	valid_check(char *line, int *flag, int *status)
{
	int		total_quots;
	int		total_dub_quots;
	int		i;

	i = 0;
	total_quots = 0;
	total_dub_quots = 0;
	if (line == NULL || !ft_strncmp(line, "\n", ft_strlen(line)) || \
	check_space(line) == 1)
	{
		if (line == NULL)
			(*flag) = 1;
		else if (!ft_strncmp(line, "\n", ft_strlen(line)) || \
		check_space(line) == 1)
			(*flag) = 2;
		return (-1);
	}
	if (count_quots(&total_quots, &total_dub_quots, line) == 1)
		return (-100);
	while (line[i] == ' ')
		i++;
	if (line[i] == '|')
		return (-258);
	status = flag;
	return (i);
}

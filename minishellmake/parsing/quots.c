/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quots.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:20:58 by eheike            #+#    #+#             */
/*   Updated: 2022/06/23 17:56:13 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*del_quots(char *line, char **env)
{
	int		i;
	int		j;
	int		start;
	int		end;
	int		flag;
	char	*buf;
	char	*tmp;
	char	*tmp2;
	char	c;

	i = 0;
	end = 0;
	start = 0;
	while (line[i])
	{
		flag = 0;
		while (line[i] && line[i] != 34 && line[i] != 39 && line[i] != '$')
			i++;
		if (!line[i])
			return (line);
		else if (line[i] == 34)
		{
			flag = 1;
			start = i;
			i++;
			while (line[i] != 34)
			{
				while (line[i] != '$' && line[i] != 34)
					i++;
				if (line[i] == '$')
					line = change_var(line, &i, env);
			}
			end = i;
		}
		else if (line[i] == 39)
		{
			flag = 1;
			start = i;
			i++;
			while (line[i] != 39)
				i++;
			end = i;
		}
		else if (line[i] == '$')
		{
			line = change_var(line, &i, env);
			//printf("line bez $ = %s (%zu)\n", line, ft_strlen(line));
		}
		if (flag == 1)
		{
			buf = NULL;
			if (start > 0)
			{
				buf = ft_substr(line, 0, start);
			}
			if (end > start + 1)
			{
				tmp = ft_substr(line, start + 1, end - start - 1);
				if (buf == NULL)
					buf = tmp;
				else
				{
					buf = ft_strjoin(buf, tmp);
					free(tmp);
				}
			}
			if (ft_strlen(line) > end + 2)
			{
				tmp = ft_substr(line, end + 1, ft_strlen(line) - end - 1);
				if (buf == NULL)
					buf = tmp;
				else
				{
					buf = ft_strjoin(buf, tmp);
					free(tmp);
				}
			}
			free(line);
			line = buf;
			if (line == NULL)
			{
				line = malloc(sizeof(char) * 1);
				line = "\0";
				return (line);
			}
			i = i - 2;
		}
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

void	count_quots(int *q, int *dub_q, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] != 34 && line[i] != 39)
			i++;
		if (!line[i])
			return ;
		else if (line[i] == 34)
		{
			(*dub_q)++;
			i++;
			while (line[i] && line[i] != 34)
				i++;
			if (line[i] == 34)
				(*dub_q)++;
		}
		else if (line[i] == 39)
		{
			(*q)++;
			i++;
			while (line[i] && line[i] != 39)
				i++;
			if (line[i] == 39)
				(*q)++;
		}
		i++;
	}
	if (*dub_q % 2 || *q % 2)
		exit(1); // ошибка, нечетное количество кавычек
}
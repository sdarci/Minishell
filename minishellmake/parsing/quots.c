/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quots.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:20:58 by eheike            #+#    #+#             */
/*   Updated: 2022/06/21 17:56:01 by eheike           ###   ########.fr       */
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
				{
					printf("i = %d\n", i);
					line = change_var(line, &i, env);
					printf("i posle = %d\n", i);
				}
			}
			//i++;
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
			printf("i posle = %d\n", i);
			//printf("line bez $ = %s (%zu)\n", line, ft_strlen(line));
			//i++;
		}
		if (flag == 1)
		{
			buf = NULL;
			printf("line posle cut $ = %s, len = %zu\n", line, ft_strlen(line));
			printf("buf0 = %s\n", buf);
			// while (line[i] != 34 && line[i] != 39)
			// 	i++;
			// c = line[i];
			if (start > 0)
			{
				buf = ft_substr(line, 0, start);
				printf("buf1 = %s\n", buf);
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
				printf("buf2 = %s\n", buf);
			}
			printf("ft_strlen(line) = %zu, end + 1 = %d, line[end] = %c \n", ft_strlen(line), end + 1, line[end]);
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
				printf("buf3 = %s\n", buf);
			}
			free(line);
			line = buf;
			printf("line = %s\n", line);
			if (line == NULL)
			{
				line = malloc(sizeof(char) * 1);
				line = "\0";
				return (line);
			}
			i = i - 2;
		}
		if (line && line[i])
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
	printf("q = %d, dub_q = %d\n", *q, *dub_q);
	if (*dub_q % 2 || *q % 2)
		exit(1); // ошибка, нечетное количество кавычек
}
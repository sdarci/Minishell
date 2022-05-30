/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:24:50 by eheike            #+#    #+#             */
/*   Updated: 2022/05/26 15:51:56 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft_exp.c"

char	*replace_env(struct env1 **list_of_env, char *line)
{
	struct env1	*tmp;
	char		*buf;
	char		*temp;
	char		**arr;
	int			i;
	int			j;
	int			flag;

	arr = ft_split(line, '$');
	if (line[0] == '$')
		i = 0;
	else
		i = 1;
	flag = 0;
	while (arr[i])
	{
		tmp = *list_of_env;
		j = 0;
		while (arr[i][j] && arr[i][j] != '<' && arr[i][j] != '>' && arr[i][j] != 34 && arr[i][j] != 39)
			j++;
		while (tmp)
		{
			buf = ft_substr(arr[i], 0, (ft_strlen(tmp->key) + 1));
			if (!ft_strncmp(buf, tmp->key, ft_strlen(buf)))
			{
				free(buf);
				buf = ft_strjoin(tmp->value, (arr[i] + ft_strlen(tmp->key) + 1));
				free(arr[i]);
				arr[i] = buf;
				flag = 1;
			}
			
			if (flag == 0)
			{
				free (buf);
				if (tmp->next == NULL)
				{
					buf = ft_strdup(arr[i] + j);
					free (arr[i]);
					arr[i] = buf;
				}
			}
			tmp = tmp->next;
		}
		i++;
	}
	buf = ft_strdup(arr[0]);
	i = 1;
	while (arr[i])
	{
		temp = buf;
		buf = ft_strjoin(buf, arr[i]);
		free (temp);
		i++;
	}
	return (buf);
}

void	check_env(char **line, char **env)
{
	struct env1	*list_of_env;
	int			i;
	char		*tmp;
	char		*buf;
	char		**arr;

	i = 0;
	list_of_env = env_list(0, NULL, env);
	arr = ft_split(*line, ' ');
	while (arr[i])
	{
		buf = replace_env(&list_of_env, arr[i]);
		free(arr[i]);
		arr[i] = buf;
		i++;
	}
	buf = ft_strdup(arr[0]);
	i = 1;
	while (arr[i])
	{
		tmp = buf;
		buf = ft_strjoin(buf, " ");
		free (tmp);
		tmp = buf;
		buf = ft_strjoin(buf, arr[i]);
		free (tmp);
		i++;
	}
	*(line) = buf;
}
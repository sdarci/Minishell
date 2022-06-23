/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:24:50 by eheike            #+#    #+#             */
/*   Updated: 2022/06/22 18:55:01 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_var(char *var, char **env)
{
	struct env1	*list_of_env;
	struct env1	*tmp;

	list_of_env = env_list(env);
	tmp = list_of_env;
	while (tmp)
	{
		if (!ft_strncmp(var, tmp->key, ft_strlen(var)))
			return (tmp->value);
		else
			tmp = tmp->next;
	}
	free(var);
	return (NULL);
}

char	*repl_line(char *line, int start, char *val, int *len)
{
	char	*buf;
	char	*res;
	char	*tmp;

	buf = ft_substr(line, 0, start - 1);
	res = ft_strdup(buf);
	free(buf);
	if (val != NULL)
	{
		buf = ft_strdup(val);
		tmp = res;
		res = ft_strjoin(res, buf);
		free(tmp);
		free(buf);
	}
	buf = ft_substr(line, *len, ft_strlen(line) + (*len));
	tmp = res;
	res = ft_strjoin(res, buf);
	free(tmp);
	free(buf);
	if (val != NULL)
		(*len) = start + ft_strlen(val) - ((*len) - start - 1);
	else
		(*len) = start - 1;
	return(res);
}

char	*change_var(char *line, int *i, char **env)
{
	char	*buf;
	char	*val;
	int		a;
	int		j;

	(*i)++;
	a = *i;
	while ((line[a] > 47 && line[a] < 58) || (line[a] > 64 && line[a] < 91) || (line[a] > 96 && line[a] < 123) || line[a] == 95 || line[a] == 63)
		a++;
	if (a > *i)
	{
		buf = (char *)malloc(sizeof(char) * (a - (*i) + 1));
		j = 0;
		while (*i < a)
		{
			buf[j] = line[*i];
			(*i)++;
			j++;
		}
		buf[j] = '\0';
		val = find_var(buf, env);
		line = repl_line(line, (*i) - j, val, i);
		if (val != NULL)
			free(val);
	}
	else if (line[a] == 34 || line[a] == 39)
	{
		line = repl_line(line, (*i), NULL, i);
		(*i)--;
	}
	return(line);
}
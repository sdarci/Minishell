/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:24:50 by eheike            #+#    #+#             */
/*   Updated: 2022/06/30 21:42:55 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_st(char *var)
{
	char	*res;

	if (!ft_strncmp(var, "?", ft_strlen(var)))
	{
		res = ft_itoa(g_lobal_status);
		free(var);
		return (res);
	}
	return (NULL);
}

static char	*find_var(char *var, char **env)
{
	struct env1	*list_of_env;
	struct env1	*tmp;
	char		*res;

	res = get_st(var);
	if (res)
		return (res);
	list_of_env = env_list(env);
	tmp = list_of_env;
	while (tmp)
	{
		if (!ft_strncmp(var, tmp->key, ft_strlen(tmp->key)) \
		&& ft_strlen(tmp->key) == ft_strlen(var))
		{
			res = ft_strdup(tmp->value);
			free_env(list_of_env);
			free(var);
			return (res);
		}
		else
			tmp = tmp->next;
	}
	free(var);
	free_env(list_of_env);
	return (NULL);
}

static char	*find_val_of_var(int *i, char *line, char **env, int a)
{
	char	*buf;
	char	*val;
	int		j;

	buf = (char *)malloc(sizeof(char) * (a - (*i) + 1));
	j = 0;
	while (*i < a)
		buf[j++] = line[(*i)++];
	buf[j] = '\0';
	val = find_var(buf, env);
	line = repl_line(line, (*i) - j, val, i);
	if (val != NULL)
		free(val);
	return (line);
}

char	*change_var(char *line, int *i, char **env, int flg)
{
	int		a;
	char	*tmp;

	tmp = line;
	(*i)++;
	a = *i;
	while ((line[a] > 47 && line[a] < 58) || (line[a] > 64 && line[a] < 91) \
	|| (line[a] > 96 && line[a] < 123) || line[a] == 95 || line[a] == 63)
		a++;
	if (a > *i)
	{
		line = find_val_of_var(i, line, env, a);
		if (line == NULL)
			return (NULL);
	}
	else if ((line[a] == 34 || line[a] == 39) && flg)
	{
		line = repl_line(line, (*i), NULL, i);
		if (line == NULL)
			return (NULL);
		(*i)--;
	}
	free(tmp);
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:24 by eheike            #+#    #+#             */
/*   Updated: 2022/06/27 17:56:01 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_parse_value(char *argv)
{
	int		i;
	int		flg;
	char	*line;

	i = 0;
	flg = 0;
	while (argv[i] != '=')
		i++;
	flg = i;
	while (argv[i])
		i++;
	line = (char *)malloc(sizeof(char) * (i - flg + 1));
	i = flg;
	i = 0;
	while (argv[flg++])
	{
		line[i] = argv[flg];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_parse_key(char *argv)
{
	int		i;
	char	*line;

	i = 0;
	while (argv[i] != '=')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (argv[i] != '=')
	{
		line[i] = argv[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

struct env1	*env_list(char **env)
{
	struct env1	*env1;
	struct env1	*temp;
	struct env1	*p;
	int			i;

	i = 0;
	env1 = (struct env1 *)malloc(sizeof(struct env1));
	if (!env1)
		return (NULL);
	env1->key = ft_parse_key(env[i]);
	env1->value = ft_parse_value(env[i]);
	env1->next = NULL;
	while (env[++i] != NULL)
	{
		temp = (struct env1 *)malloc(sizeof(struct env1));
		p = env1->next;
		temp->key = ft_parse_key(env[i]);
		temp->value = ft_parse_value(env[i]);
		temp->next = p;
		env1->next = temp;
	}
	return (env1);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		free(env->key);
		free(env->value);
		env = env->next;
		free(tmp);
	}
}

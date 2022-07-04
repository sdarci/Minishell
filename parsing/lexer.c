/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 19:30:05 by eheike            #+#    #+#             */
/*   Updated: 2022/06/29 19:41:38 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	lexer_err(char **arr)
{
	if (arr == NULL)
	{
		parse_error(NULL, NULL, 1);
		return (1);
	}
	if (check_void_pipe(arr) == 1)
	{
		free(arr);
		parse_error(NULL, "|", 258);
		return (1);
	}
	return (0);
}

static int	check_trim(char **arr, int i)
{
	if (arr[i] == NULL)
	{
		while (i >= 0)
			free(arr[i--]);
		free(arr);
		parse_error(NULL, NULL, 1);
		return (1);
	}
	return (0);
}

t_tok	*lexer(char *line, int i, char **env, int total_pipes)
{
	char	**arr;
	t_tok	*tokens;
	char	*buf;

	arr = mini_split(total_pipes, line, '|');
	if (lexer_err(arr) == 1)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		buf = arr[i];
		arr[i] = ft_strtrim(arr[i], ISSPACE);
		free(buf);
		if (check_trim(arr, i) == 1)
			return (NULL);
		i++;
	}
	tokens = create_token_list(arr, total_pipes, env);
	free(arr);
	if (tokens == NULL)
	{
		parse_error(NULL, NULL, 1);
		return (NULL);
	}
	return (tokens);
}

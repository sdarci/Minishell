/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:19:27 by eheike            #+#    #+#             */
/*   Updated: 2022/06/20 18:09:20 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rec_cmd(t_tok **toks, int *i)
{
	int		j;
	int		a;
	char	*buf;
	char	*tmp;
	char	c;

	while ((*toks)->line[*i] && (*toks)->line[*i] != '>' && (*toks)->line[*i] != '<')
	{
		j = (*i);
		a = 0;
		if ((*toks)->line[*i] == 34 || (*toks)->line[*i] == 39)
		{
			c = (*toks)->line[*i];
			(*i)++;
			while ((*toks)->line[*i] != c)
				(*i)++;
			buf = ft_substr((*toks)->line, j, (*i) - j + 1);
			// buf = (char *)malloc(sizeof(char) * (*i - j + 1));
			// if (buf == NULL)
			// 	return ;// вернуть ошибку
			// while (j <= *i)
			// 	buf[a++] = (*toks)->line[j++];
			// buf[a] = '\0';
			if ((*toks)->cmd == NULL)
				(*toks)->cmd = buf;
			else
			{
				//tmp = (*toks)->cmd;
				(*toks)->cmd = ft_strjoin((*toks)->cmd, buf);
				//free(tmp);
			}
			if ((*toks)->line[*i])
				(*i)++;
		}
		else
		{
			while ((*toks)->line[*i] && (*toks)->line[*i] != '>' && (*toks)->line[*i] != '<' && (*toks)->line[*i] != 34 && (*toks)->line[*i] != 39)
				(*i)++;
			if (*i > j)
			{
				buf = (char *)malloc(sizeof(char) * (*i - j + 1));
				if (buf == NULL)
					return ;// вернуть ошибку
				while (j < *i)
					buf[a++] = (*toks)->line[j++];
				buf[a] = '\0';
				if ((*toks)->cmd == NULL)
					(*toks)->cmd = buf;
				else
				{
					//tmp = (*toks)->cmd;
					(*toks)->cmd = ft_strjoin((*toks)->cmd, buf);
					//free(tmp);
				}
			}
		}
	}
}

int	check_cmd_build_in(t_tok *tok)
{
	t_list	*list_of_bilds;
	t_list	*tmp;

	list_of_bilds = list_of_bildins();
	tmp = list_of_bilds;
	while (tmp)
	{
		if (tok->cmd_arr[0] == NULL)
			return (-1);
		if (ft_strncmp(tok->cmd_arr[0], tmp->data, ft_strlen(tok->cmd_arr[0])) == 0)
		{
			//del_list(&list_of_bilds);//освободить массив и все его внутренние маллоки
			return (tmp->type);
		}
		tmp = tmp->next;
	}
	//del_list(&list_of_bilds);
	return (0);
}
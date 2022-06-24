/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <sdarci@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:27:21 by eheike            #+#    #+#             */
/*   Updated: 2022/06/24 18:02:24 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void	find_spec(t_tok **tokens)
{
	int		i;
	t_tok	*tmp;
	char	c;

	tmp = *tokens;
	while (tmp)
	{
		i = 0;
		while (tmp->line[i])
		{
			if (tmp->line[i] == 34 || tmp->line[i] == 39)
			{
				c = tmp->line[i];
				i++;
				while (tmp->line[i] != c && tmp->line[i])
					i++;
			}
			if (tmp->line[i] == '>')
			{
				count_redir(&i, '>', &tmp);
				if (!tmp->line[i] || tmp->line[i] == '<' || tmp->line[i] == '>')
					exit(1);//некорректный символ после '<' 258
				i--;
			}	
			else if (tmp->line[i] == '<')
			{
				count_redir(&i, '<', &tmp);
				if (!tmp->line[i] || tmp->line[i] == '<' || tmp->line[i] == '>')//подправить
					exit(1);//некорректный символ после '<' 258
				i--;
			}
			i++;
		}
		tmp = tmp->next;
	}
}

void	parse_of_line(t_tok **tokens) // больше 25 строк
{
	int		i;
	t_tok	*tmp;
	char	*tmp1;

	tmp = *tokens;
	find_spec(tokens);
	while (tmp)
	{
		i = 0;
		rec_cmd(&tmp, &i);
		while (tmp->flag_r || tmp->flag_dub_r || tmp->flag_l || tmp->flag_dub_l)
		{
			rec_cmd(&tmp, &i);
			if (tmp->line[i] == '>' && tmp->line[i + 1] != '>')
				new_redir(&tmp, 1, &i, &(tmp->flag_r));
			else if (tmp->line[i] == '>' && tmp->line[i + 1] == '>')
				new_redir(&tmp, 2, &i, &(tmp->flag_dub_r));
			else if (tmp->line[i] == '<' && tmp->line[i + 1] != '<')
				new_redir(&tmp, 3, &i, &(tmp->flag_l));
			else if (tmp->line[i] == '<' && tmp->line[i + 1] == '<')
				new_redir(&tmp, 4, &i, &(tmp->flag_dub_l));
			rec_cmd(&tmp, &i);
		}
		tmp->cmd_arr = mini_split(count_del(tmp->cmd, ' '), tmp->cmd, i, ' ');
		if (tmp->cmd_arr == NULL)
			return ; // ошибка маллока 1
		i = 0;
		while (tmp->cmd_arr[i])
		{
			tmp1 = tmp->cmd_arr[i];
			tmp->cmd_arr[i] = ft_strtrim(tmp->cmd_arr[i], ISSPACE);
			if (tmp->cmd_arr[i] == NULL)
				return ; // ошибка маллока 1
			free(tmp1);
			tmp->cmd_arr[i] = del_quots(tmp->cmd_arr[i], tmp->env);
			i++;
		}
		//tmp->f_build_in = check_cmd_build_in(tmp);
		tmp = tmp->next;
	}
}

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
	return(0);
}

//void	parse_error(char)


int check_space(char *line)
{
    int i;
    i = 0;
    while (line[i])
    {
        if (line[i] != 32)
            return (0);
        i++;
    }
    return (1);
}


t_tok	*parse(char *line, char *env[], int *flag, int *status) //больше 25 строк и 4 переменных
{
	int		i;
	int		total_pipes;
	int		total_quots;
	int		total_dub_quots;
	char	**arr;
	char	*buf;
	t_tok	*tokens;
	char	c;
	
	total_pipes = 0;
	total_quots = 0;
	total_dub_quots = 0;
	i = 0;
	if (line == NULL || !ft_strncmp(line, "\n", ft_strlen(line)))
	{
		if (line == NULL)
			(*flag) = 1;
		else if (!ft_strncmp(line, "\n", ft_strlen(line)))
			(*flag) = 2;
		return (NULL); // не менять статус
	}
	if (check_space(line) == 1)
    {
        (*flag) = 2;
        return (NULL);
    }
	count_quots(&total_quots, &total_dub_quots, line);
	while (line[i] == ' ')
		i++;
	if (line[i] == '|')
		return (NULL); //ошибка, труба не может быть первой 258
	while (line[i])
	{
		i = skip_quots(line, "|", i);
		if (line[i] == '|')
			total_pipes++;
		if (line[i] == '|' && line[i - 1] == '|')
			return (NULL); // 2 трубы подряд 258
		i++;
	}
	arr = mini_split(total_pipes, line, i, '|');
	if (arr == NULL)
		return (NULL); // проблема с маллок 1
	if (check_void_pipe(arr) == 1)
		return (NULL); // между трубами пусто 258
	i = 0;
	while (arr[i])
	{
		buf = arr[i];
		arr[i] = ft_strtrim(arr[i], ISSPACE);
		free(buf);
		i++;
	}
	tokens = create_token_list(arr, total_pipes, env);
	free(arr);
	parse_of_line(&tokens);
	return (tokens);
}

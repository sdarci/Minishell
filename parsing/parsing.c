/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:27:21 by eheike            #+#    #+#             */
/*   Updated: 2022/05/31 20:20:04 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	find_double()
{

}

void	find_spec(t_tok **tokens)
{
	int		i;
	t_tok	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		i = 0;
		while (tmp->line[i])
		{
			if (tmp->line[i] == '>')
			{
				if (tmp->line[i + 1] != '>')
					tmp->flag_r++;
				else
				{
					tmp->flag_dub_r++;
					i++;
				}
				i++;
				while (tmp->line[i] == ' ')
					i++;
				if (!tmp->line[i] || tmp->line[i] == '<' || tmp->line[i] == '>')
					exit(1);//некорректный символ после '<'
			}	
			else if (tmp->line[i] == '<')
			{
				if (tmp->line[i + 1] != '<')
					tmp->flag_l++;
				else
				{
					tmp->flag_dub_l++;
					i++;
				}
				i++;
				while (tmp->line[i] == ' ')
					i++;
				if (!tmp->line[i] || tmp->line[i] == '<' || tmp->line[i] == '>')
					exit(1);//некорректный символ после '<'
			}
			i++;
		}
		tmp = tmp->next;
	}
}

void	new_redir(t_tok **toks, int type, int *i, int *flag)
{
	int		j;
	int		a;
	t_redir	*red;

	red = create_red(type);
	if (type % 2)
		(*i)++;
	else
		(*i) += 2;
	if ((*toks)->line[*i] == ' ')
		(*i)++;
	j = *i;
	while ((*toks)->line[*i] && (*toks)->line[*i] != ' ' && (*toks)->line[*i] != '>' && (*toks)->line[*i] != '<')
		(*i)++;
	red->name = (char *)malloc(sizeof(char) * (*i - j + 1));
	if (red->name == NULL)
		return ;// вернуть ошибку
	a = 0;
	while (j < *i)
		red->name[a++] = (*toks)->line[j++];
	red->name[a] = '\0';
	add_red(&(*toks)->redir, red);
	(*flag)--;
}

void	rec_cmd(t_tok **toks, int *i)
{
	int		j;
	int		a;
	char	*buf;
	char	*tmp;

	if ((*toks)->line[*i] != '>' && (*toks)->line[*i] && (*toks)->line[*i] != '<')
	{
		j = *i;
		a = 0;
		while ((*toks)->line[*i] != '>' && (*toks)->line[*i] != '<')
			(*i)++;
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
			tmp = (*toks)->cmd;
			(*toks)->cmd = ft_strjoin((*toks)->cmd, buf);
			free(tmp);
		}	
	}
}

void	parse_of_line(t_tok **tokens, char **env)
{
	int		i;
	char	*buf;
	t_tok	*tmp;

	tmp = *tokens;
	find_spec(tokens);
	while (tmp)
	{
		check_env(&(tmp->line), env);
		i = 0;
		while (tmp->flag_r || tmp->flag_dub_r || tmp->flag_l || tmp->flag_dub_l)
		{
			rec_cmd(&tmp, &i);
			if (tmp->line[i] == '>' && tmp->line[i + 1] == '>')
				new_redir(&tmp, 2, &i, &(tmp->flag_dub_r));
			else if (tmp->line[i] == '>' && tmp->line[i + 1] != '>')
				new_redir(&tmp, 1, &i, &(tmp->flag_r));
			else if (tmp->line[i] == '<' && tmp->line[i + 1] != '<')
				new_redir(&tmp, 3, &i, &(tmp->flag_l));
			else if (tmp->line[i] == '<' && tmp->line[i + 1] == '<')
			{
				new_redir(&tmp, 4, &i, &(tmp->flag_dub_l));
				//buf = readline настроить библиотеку ридлайн и добавить функцию для считывания из ввода
			}
		}
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

t_tok	*parse(char *line, char *env[])
{
	int		i;
	int		total_pipes;
	char	**arr;
	char	*buf;
	t_tok	*tokens;
	
	total_pipes = 0;
	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '|')
		return (NULL); //ошибка, труба не может быть первой
	while (line[i])
	{
		if (line[i] == '|') // придумать проверку если между двумя трубами только пробелы
			total_pipes++;
		if (line[i] == '|' && line[i - 1] == '|')
			return (NULL);
		i++;
	}
	arr = ft_split(line, '|');
	if (arr == NULL)
		return (NULL); // проблема с маллок
	if (check_void_pipe(arr) == 1)
		return (NULL); // между трубами пусто
	i = 0;
	while (arr[i])
	{
		buf = arr[i];
		arr[i] = ft_strtrim(arr[i], " ");
		free(buf);
		i++;
	}
	tokens = create_token_list(arr, total_pipes); // если последняя строка пустая, чтение последней команды из ввода
	free(arr);
	parse_of_line(&tokens, env);
	return (tokens);
}

int	main(int argc, char **argv, char *envp[])
{
	char	*str;
	t_tok	*tok;
	t_tok	*tmp;

	//str = "jhghjk|jkhg|kjkh";
	//printf("%s\n", argv[1]);
	tok = parse(argv[1], envp);
	if (tok == NULL)
		return (1);
	tmp = tok;
	while (tmp->next)
	{
		printf("line : %s\ncmd : %s\n%d / %d, > %d, >> %d\n", tmp->line, tmp->cmd, tmp->num, tmp->total, tmp->flag_r, tmp->flag_dub_r);
		//printf("%d, %s\n", tmp->redir->type_re, tmp->redir->name);
		//printf("%p\n", tmp->redir);
		if (tmp->redir != NULL)
			//printf("%d, %s\n", tmp->redir->next->type_re, tmp->redir->next->name);
			printf("%d, %s\n\n", tmp->redir->type_re, tmp->redir->name);
		tmp = tmp->next;
	}
	printf("line : %s\ncmd : %s\n%d / %d, > %d, >> %d\n", tmp->line, tmp->cmd, tmp->num, tmp->total, tmp->flag_r, tmp->flag_dub_r);
	if (tmp->redir != NULL)
		//printf("%d, %s\n", tmp->redir->next->type_re, tmp->redir->next->name);
		printf("%d, %s\n", tmp->redir->type_re, tmp->redir->name);
}
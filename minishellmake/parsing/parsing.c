/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <sdarci@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:27:21 by eheike            #+#    #+#             */
/*   Updated: 2022/06/12 16:11:23 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	count_redir(int *i, char c, t_tok **tmp)
{
	int	*flag;
	int	*flag_dub;

	flag = &(*tmp)->flag_l;
	flag_dub = &(*tmp)->flag_dub_l;
	if (c == '>')
	{
		flag = &(*tmp)->flag_r;
		flag_dub = &(*tmp)->flag_dub_r;
	}
	if ((*tmp)->line[*i + 1] != c)
		(*flag)++;
	else
	{
		(*flag_dub)++;
		(*i)++;
	}
	(*i)++;
	while ((*tmp)->line[*i] == ' ')
		(*i)++;
	if ((flag || flag_dub) && (*tmp)->red == NULL)
		(*tmp)->red = init_red();
	return ;
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
				count_redir(&i, '>', &tmp);
				if (!tmp->line[i] || tmp->line[i] == '<' || tmp->line[i] == '>')
					exit(1);//некорректный символ после '<'
			}	
			else if (tmp->line[i] == '<')
			{
				count_redir(&i, '<', &tmp);
				if (!tmp->line[i] || tmp->line[i] == '<' || tmp->line[i] == '>')//подправить
					exit(1);//некорректный символ после '<'
			}
			i++;
		}
		tmp = tmp->next;
	}
}

void	sort_of_redir(t_tok **toks, int type, char *buf)
{
	t_list	*red;
	
	if ((type == 1 || type == 2) && ((*toks)->flag_r + (*toks)->flag_dub_r == 1))
	{
		(*toks)->red->out = buf;
		(*toks)->red->type_out = type;
	}
	else if ((type == 1 || type == 2) && ((*toks)->flag_r + (*toks)->flag_dub_r != 1))
	{
		red = create_node(buf, type);
		add_node(&(*toks)->create, red);
	}
	else if ((type == 3 || type == 4) && ((*toks)->flag_l + (*toks)->flag_dub_l == 1))
	{
		(*toks)->red->in = buf;
		(*toks)->red->type_in = type;
	}
	else if ((type == 3 || type == 4) && ((*toks)->flag_l + (*toks)->flag_dub_l != 1))
	{
		red = create_node(buf, type);
		add_node(&(*toks)->check, red);
	}
	return ;
}

void	new_redir(t_tok **toks, int type, int *i, int *flag)
{
	int		j;
	int		a;
	char	*buf;

	if (type == 1 || type == 3)
		(*i)++;
	else if (type == 2 || type == 4)
		(*i) += 2;
	if ((*toks)->line[*i] == ' ')
		(*i)++;
	j = *i;
	while ((*toks)->line[*i] && (*toks)->line[*i] != ' ' && (*toks)->line[*i] != '>' && (*toks)->line[*i] != '<')
		(*i)++;
	buf = (char *)malloc(sizeof(char) * (*i - j + 3));
	if (buf == NULL)
		exit(1);// вернуть ошибку
	a = 0;
	while (j < *i)
		buf[a++] = (*toks)->line[j++];
	buf[a] = '\0';
	sort_of_redir(toks, type, buf);
	(*flag)--;
	return ;
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
		while ((*toks)->line[*i] && (*toks)->line[*i] != '>' && (*toks)->line[*i] != '<')
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

int	check_cmd_build_in(t_tok *tok)
{
	t_list	*list_of_bilds;
	t_list	*tmp;

	list_of_bilds = list_of_bildins();
	tmp = list_of_bilds;
	while (tmp)
	{
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

void	parse_of_line(t_tok **tokens, char **env) // больше 25 строк
{
	int		i;
	char	*buf;
	char	*fr;
	t_tok	*tmp;

	tmp = *tokens;
	find_spec(tokens);
	while (tmp)
	{
		check_env(&(tmp->line), env);
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
			while (tmp->line[i] == ' ')
				i++;
			rec_cmd(&tmp, &i);
		}
		tmp->cmd_arr = ft_split(tmp->cmd, ' ');//перевод команды из строки в массив
		tmp->f_build_in = check_cmd_build_in(tmp);//проверка команды на то, является ли она билд ином
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

t_tok	*parse(char *line, char *env[]) //больше 25 строк и 4 переменных
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

// int	main(int argc, char **argv, char *envp[])
// {
// 	char	*str;
// 	t_tok	*tok;
// 	t_tok	*tmp;
// 	t_list *tmp_r;

// 	//str = "ls > file1 > file2 > file3 >file4";
// 	//printf("%s\n", argv[1]);
// 	tok = parse(argv[1], envp);
// 	if (tok == NULL)
// 		return (1);
// 	tmp = tok;
// 	while (tmp->next)
// 	{
// 		printf("line: %s\ncmd : %s(%d)\n%d / %d\nin: %s; out: %s\n", tmp->line, tmp->cmd_arr[0], tmp->f_build_in, tmp->num, tmp->total, tmp->red->in, tmp->red->out);
// 		//printf("%d, %s\n", tmp->redir->type_re, tmp->redir->name);
// 		//printf("%p\n", tmp->redir);
// 		if (tmp->create != NULL)
// 		{
// 		// 	printf("privet\n");
// 			tmp_r = tmp->create;
// 			while (tmp_r)
// 			{
// 				printf("redirecty : %s\n\n", tmp_r->data);
// 				tmp_r = tmp_r->next;
// 			}
// 			//printf("redirecty : %s\n\n", tmp_r->data);
// 		}
// 		tmp = tmp->next;
// 	}
// 	printf("line 1: %s\ncmd : %s(%d)\n%d / %d\nin: %s; out: %s\n", tmp->line, tmp->cmd_arr[0], tmp->f_build_in, tmp->num, tmp->total, tmp->red->in, tmp->red->out);
// 	 if (tmp->check != NULL)
// 	// 	{
// 	// 		//printf("privet\n");
// 			tmp_r = tmp->check;
// 			while (tmp_r)
// 			{
// 				printf("redirecty : %s\n\n", tmp_r->data);
// 				tmp_r = tmp_r->next;
// 			}
// 	// 	}
// 	// if (tmp->redir != NULL)
// 	// 	//printf("%d, %s\n", tmp->redir->next->type_re, tmp->redir->next->name);
// 	// 	printf("%d, %s\n", tmp->redir->type_re, tmp->redir->name);
// }
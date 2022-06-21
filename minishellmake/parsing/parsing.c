/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:27:21 by eheike            #+#    #+#             */
/*   Updated: 2022/06/21 15:06:35 by eheike           ###   ########.fr       */
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
				//i++;
			}
			if (tmp->line[i] == '>')
			{
				count_redir(&i, '>', &tmp);
				if (!tmp->line[i] || tmp->line[i] == '<' || tmp->line[i] == '>')
					exit(1);//некорректный символ после '<'
				i--; // посмотреть почему накручивается лишний раз счетчик
			}	
			else if (tmp->line[i] == '<')
			{
				count_redir(&i, '<', &tmp);
				if (!tmp->line[i] || tmp->line[i] == '<' || tmp->line[i] == '>')//подправить
					exit(1);//некорректный символ после '<'
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
		// if (tmp->red)
		// {
		// 	if (tmp->red->in)
		// 		tmp->red->in = del_quots(tmp->red->in, tmp->env);
		// 	if (tmp->red->out)
		// 		tmp->red->out = del_quots(tmp->red->out, tmp->env);
		// }
		//printf("razdelenie po probelam\n");
		//printf("cmd = %s\n", tmp->cmd);
		tmp->cmd_arr = mini_split(count_del(tmp->cmd, ' '), tmp->cmd, i, ' ');
		if (tmp->cmd_arr == NULL)
			return ;
		//tmp->cmd_arr = ft_split(tmp->cmd, 32);
		i = 0;
		while (tmp->cmd_arr[i])
		{
			tmp->cmd_arr[i] = del_quots(tmp->cmd_arr[i], tmp->env);
			//printf("cmd line posle : %s\n", tmp->cmd_arr[i]);
			i++;
		}
		//del_quots(tmp->cmd, env);
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

t_tok	*parse(char *line, char *env[], int *flag) //больше 25 строк и 4 переменных
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
		return (NULL);
	}
	count_quots(&total_quots, &total_dub_quots, line);
	while (line[i] == ' ') //тримом обрезать все исспейсы вначале и в конце
		i++;
	if (line[i] == '|')
		return (NULL); //ошибка, труба не может быть первой
	while (line[i])
	{
		while (line[i] != 34 && line[i] != 39 && line[i] && line[i] != '|')
			i++;
		if (line[i] == 34 || line[i] == 39) // есть такой же код, заменить на функцию
		{
			c = line[i];
			i++;
			while (line[i] != c)
				i++;
		}
		if (line[i] == '|') // придумать проверку если между двумя трубами только пробелы
			total_pipes++;
		if (line[i] == '|' && line[i - 1] == '|')
			return (NULL);
		i++;
	}
	//printf("total pipes = %d\n", total_pipes);
	arr = mini_split(total_pipes, line, i, '|');
	//arr = mini_split(total_pipes, line, i, '|');
	if (arr == NULL)
		return (NULL); // проблема с маллок
	if (check_void_pipe(arr) == 1)
		return (NULL); // между трубами пусто
	i = 0;
	while (arr[i])
	{
		//printf("i = %d arr[i] = %s \n", i, arr[i]);
		//buf = arr[i];
		arr[i] = ft_strtrim(arr[i], " ");
		//free(buf);
		i++;
	}
	//printf("i = %d arr[i] = %s \n", i, arr[i]);
	tokens = create_token_list(arr, total_pipes, env); // если последняя строка пустая, чтение последней команды из ввода
	free(arr);
	parse_of_line(&tokens);
	return (tokens);
}

// int	main(int argc, char **argv, char *envp[])
// {
// 	//char	*str;
// 	t_tok	*tok;
// 	//t_tok	*tmp;
// 	//t_list *tmp_r;
// 	//int		fd;
// 	//char	buf[29];
// 	char	*str;
// 	//int i;
// 	//int	a;

// 	//str = "ls > file1 > file2 > file3 >file4";
// 	// printf("argc = %d\n", argc);
// 	// printf("%s\n", argv[1]);
// 	str = readline("str: ");
// 	printf("readline = %s\n", str);
// 	printf("%d %s\n", argc, argv[1]);
// 	//fd = open(argv[1], O_RDONLY);
// 	//buf = (char *)malloc(27);
// 	//read(fd, buf, 28);
// 	//buf[28] = '\0';
// 	//tok = parse(argv[1], envp);
// 	// printf("buf = %s\n", buf);
// 	tok = parse(str, envp);
// 	if (tok == NULL)
// 		return (1);
// 	// tmp = tok;
// 	// a = 0;
// 	// while (tmp->next)
// 	// {
// 	// 	printf("line: %s\ncmd : %s(%d)\n%d / %d\nin: %s; out: %s\n", tmp->line, tmp->cmd_arr[0], tmp->f_build_in, tmp->num, tmp->total, tmp->red->in, tmp->red->out);
// 	// 	//printf("%d, %s\n", tmp->redir->type_re, tmp->redir->name);
// 	// 	//printf("%p\n", tmp->redir);
// 	// 	while (tmp->cmd_arr[a])
// 	// 		{
// 	// 			printf("cmd %d : %s\n", a, tmp->cmd_arr[a]);
// 	// 			a++;
// 	// 		}
// 	// 	if (tmp->create != NULL)
// 	// 	{
// 	// 	// 	printf("privet\n");
// 	// 		tmp_r = tmp->create;
// 	// 		while (tmp_r)
// 	// 		{
// 	// 			printf("redirecty : %s\n\n", tmp_r->data);
// 	// 			tmp_r = tmp_r->next;
// 	// 		}
// 	// 		//printf("redirecty : %s\n\n", tmp_r->data);
// 	// 	}
// 	// 	tmp = tmp->next;
// 	//}
// 	//printf("line 1: %s\ncmd : %s(%d)\n%d / %d\nin: %s; out: %s\n", tmp->line, tmp->cmd_arr[0], tmp->f_build_in, tmp->num, tmp->total, tmp->red->in, tmp->red->out);
// 	//  if (tmp->check != NULL)
// 	// // 	{
// 	// // 		//printf("privet\n");
// 	// 		tmp_r = tmp->check;
// 	// 		while (tmp_r)
// 	// 		{
// 	// 			printf("redirecty : %s\n\n", tmp_r->data);
// 	// 			tmp_r = tmp_r->next;
// 	// 		}
// 	// 	}
// 	// if (tmp->redir != NULL)
// 	// 	//printf("%d, %s\n", tmp->redir->next->type_re, tmp->redir->next->name);
// 	// 	printf("%d, %s\n", tmp->redir->type_re, tmp->redir->name);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:27:21 by eheike            #+#    #+#             */
/*   Updated: 2022/05/30 15:18:09 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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



void	parse_of_line(t_tok **tokens, char **env)
{
	int		i;
	int		j;
	int		a;
	char	*buf[2];
	t_tok	*tmp;
	t_redir	*red;

	tmp = *tokens;
	find_spec(tokens);
	
	while (tmp)
	{
		//check_env(&(tmp->line), env);
		i = 0;
		while (tmp->flag_r || tmp->flag_dub_r || tmp->flag_l || tmp->flag_dub_l)
		{
			//red = NULL;
			if (tmp->line[i] != '>')
			{
				j = i;
				a = 0;
				while (tmp->line[i] != '>')
					i++;
				buf[0] = (char *)malloc(sizeof(char) * (i - j + 1));
				while (j < i)
					buf[0][a++] = tmp->line[j++];
				buf[0][a] = '\0';
				buf[1] = ft_strtrim(buf[0], " ");
				free(buf[0]);
				tmp->to_ex = buf[1]; // правый редирект в приоритете, остальные игнорируются
									 // если > - все файлы на пути кроме конечного пустеют, 
									 // файлы рядом с остальными вариантами редиректа сохраняются такими же
									 // каждый heredoc предлагает ввести строки до ключевой строки, 
									 // но используется только если в череде редиректов он последний
			}
			if (tmp->line[i] == '>' && tmp->line[i + 1] == '>')
			{
				red = create_red(2);
				i += 2;
				if (tmp->line[i] == ' ')
					i++;
				j = i;
				while (tmp->line[i] && tmp->line[i] != 0)
					i++;
				red->name = (char *)malloc(sizeof(char) * (i - j + 1));
				a = 0;
				while (j < i)
					red->name[a++] = tmp->line[j++];
				red->name[a] = '\0';
				add_red(&tmp->redir, red);
				tmp->flag_dub_r--;
			}
			else if (tmp->line[i] == '>' && tmp->line[i + 1] != '>')
			{
				red = create_red(1);
				i++;
				if (tmp->line[i] == ' ')
					i++;
				j = i;
				while (tmp->line[i] && tmp->line[i] != 0 && tmp->line[i] != '>' && tmp->line[i] != '<')
					i++;
				red->name = (char *)malloc(sizeof(char) * (i - j + 1));
				a = 0;
				while (j < i)
					red->name[a++] = tmp->line[j++];
				red->name[a] = '\0';
				add_red(&tmp->redir, red);
				tmp->flag_r--;
			}
			else if (tmp->line[i] == '<' && tmp->line[i + 1] != '<')
			{
				red = create_red(3);
				i++;
				if (tmp->line[i] == ' ')
					i++;
				j = i;
				red->name = (char *)malloc(sizeof(char) * (i - j + 1));
				a = 0;
				while (j < i)
					red->name[a++] = tmp->line[j++];
				red->name[a] = '\0';
				add_red(&tmp->redir, red);
				tmp->flag_l--;
			}
			else if (tmp->line[i] == '<' && tmp->line[i + 1] == '<')
			{
				red = create_red(4);
				i++;
				if (tmp->line[i] == ' ')
					i++;
				j = i;
				red->name = (char *)malloc(sizeof(char) * (i - j + 1));
				a = 0;
				while (j < i)
					red->name[a++] = tmp->line[j++];
				red->name[a] = '\0';
				add_red(&tmp->redir, red);
				tmp->flag_dub_l--;
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
		printf("%s, %s, %d / %d, > %d, >> %d\n", tmp->line, tmp->to_ex, tmp->num, tmp->total, tmp->flag_r, tmp->flag_dub_r);
		//printf("%d, %s\n", tmp->redir->type_re, tmp->redir->name);
		if (tmp->redir != NULL)
			printf("%d, %s\n", tmp->redir->next->type_re, tmp->redir->next->name);
		tmp = tmp->next;
	}
	printf("%s, %s, %d / %d, > %d, >> %d\n", tmp->line, tmp->to_ex, tmp->num, tmp->total, tmp->flag_r, tmp->flag_dub_r);
}
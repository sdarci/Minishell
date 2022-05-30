/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:20:46 by eheike            #+#    #+#             */
/*   Updated: 2022/05/29 19:25:09 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
#include "LIBFT/libft.h"
#include <stdio.h>
//#include "ft_exp.c"

typedef struct s_list
{
	void			*data;
	int				type;
	struct s_list	*next;
}	t_list;

typedef struct s_redir
{
	int				type_re;
	char			*name;
	char			*text;
	struct s_redir	*next;
}	t_redir;

typedef struct s_tok
{
	int				total;
	int				num;
	int				flag_l;
	int				flag_r;
	int				flag_dub_r;
	int				flag_dub_l;
	int				flag_q;
	int				flag_dub_q;
	char			*line;
	char			*cmd;
	void			*to_ex;
	t_redir			*redir;
	struct s_tok	*next;
}	t_tok;

typedef struct s_data
{
	int		total_pipe;
	t_tok	*tokens;
	t_list	*bildins;
}	t_data;

void	find_spec(t_tok **tokens);
void	parse_of_line(t_tok **tokens, char **env);
t_tok	*parse(char *line, char *env[]);
void	check_env(char **line, char **env);
t_tok	*create_token_list(char **arr, int total);
t_redir	*create_red(int type);
t_redir *last_elem_r(t_redir *list);
void	add_red(t_redir **list, t_redir *new);
#endif
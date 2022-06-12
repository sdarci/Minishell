/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <sdarci@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:20:46 by eheike            #+#    #+#             */
/*   Updated: 2022/05/31 22:08:40 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../minishell.h"
#include "LIBFT/libft.h"
#include <stdio.h>
//# include "./minishell.h"
//#include "ft_exp.c"

typedef struct s_list
{
	void			*data;
	int				type;
	struct s_list	*next;
}	t_list;

typedef struct s_redir
{
	int				type_re; // типы редиеректа
	char			*name; // filename or limiter
	char			*text; // текст
	struct s_redir	*next; // 
}	t_redir;

typedef struct s_tok
{
	int				total; // команды между трубами (труба + 1)
	int				num; // номер команды
	int				flag_l; //
	int				flag_r; // 
	int				flag_dub_r; //
	int				flag_dub_l; //
	int				flag_q; // 
	int				flag_dub_q; //
	char			*line; // stroka s komandoi 
	char			*cmd; //comanda
	void			*to_ex; // 
	t_redir			*redir; // редиректы структура
	struct s_tok	*next; // 
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
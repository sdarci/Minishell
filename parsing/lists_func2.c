/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_func2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:21:39 by eheike            #+#    #+#             */
/*   Updated: 2022/06/29 20:34:36 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tok	*create_pipe_part(void *data, int i, int total, char **env)
{
	t_tok	*new;

	new = malloc(sizeof(t_tok));
	if (!new)
		return (NULL);
	new->line = data;
	new->num = i;
	new->env = env;
	new->total = total;
	new->flag_l = 0;
	new->flag_r = 0;
	new->flag_dub_r = 0;
	new->flag_dub_l = 0;
	new->flag_q = 0;
	new->flag_dub_q = 0;
	new->cmd = NULL;
	new->cmd_arr = NULL;
	new->red = NULL;
	new->check = NULL;
	new->next = NULL;
	return (new);
}

static void	ft_lstadd_front(t_tok **lst, t_tok *new)
{
	new->next = *lst;
	*lst = new;
}

t_tok	*create_token_list(char **arr, int total, char **env)
{
	t_tok	*list;
	t_tok	*new_node;
	int		i;

	i = total;
	list = NULL;
	while (i >= 0)
	{
		new_node = create_pipe_part(arr[i], i, total, env);
		if (new_node == NULL)
			return (NULL);
		ft_lstadd_front(&list, new_node);
		i--;
	}
	return (list);
}

void	del_list(t_list **list)
{
	t_list	*tmp;
	t_list	*del;

	tmp = *list;
	while (tmp)
	{
		del = tmp;
		tmp = NULL;
		tmp = del->next;
		free(del->data);
		free(del);
	}
}

t_redir	*init_red(void)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->in = NULL;
	new->out = NULL;
	new->type_in = 0;
	new->type_out = 0;
	return (new);
}

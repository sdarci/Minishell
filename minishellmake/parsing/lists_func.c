/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <sdarci@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:23:01 by eheike            #+#    #+#             */
/*   Updated: 2022/06/12 11:39:42 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list *create_node(void *data, int num_type)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);//вернуть ошибку
	new->data = data;
	new->type = num_type;
	new->next = NULL;
	return (new);
}

t_list *last_elem(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_node(t_list **list, t_list *new)
{
	t_list	*tmp;

	if (*list == NULL)
		*list = new;
	else
	{
		tmp = last_elem(*list);
		tmp->next = new;
		new->next = NULL;
	}
}

t_list	*add_to_bildins(char **arr_cmd)
{
	t_list	*list;
	t_list	*new_node;
	int		i;
	int		num;

	i = 0;
	num = -1;
	list = NULL;
	while (arr_cmd[i])
	{
		new_node = create_node(arr_cmd[i], num);
		add_node(&list, new_node);
		i++;
		num--;
	}
	return (list);
}

t_list	*list_of_bildins(void)
{
	t_list	*list_of_bi;
	char	**arr_cmd;

	arr_cmd = (char **)malloc(sizeof(char *) * 8);
	arr_cmd[0] = ft_strdup("echo");
	arr_cmd[1] = ft_strdup("cd");
	arr_cmd[2] = ft_strdup("pwd");
	arr_cmd[3] = ft_strdup("export");
	arr_cmd[4] = ft_strdup("unset");
	arr_cmd[5] = ft_strdup("env");
	arr_cmd[6] = ft_strdup("exit");
	arr_cmd[7] = NULL;

	list_of_bi = add_to_bildins(arr_cmd);
	free (arr_cmd);
	return (list_of_bi);
}

void	del_list(t_list **list)
{
	t_list	*tmp;
	t_list	*del;

	tmp = *list;
	while(tmp)
	{
		del = tmp;
		tmp = tmp->next;
		free(del->data);
		free(del);
	}
	free(*list);
}

t_tok *create_pipe_part(void *data, int i, int total)
{
	t_tok	*new;

	new = malloc(sizeof(t_tok));
	if (!new)
		return (NULL);//вернуть ошибку
	new->line = data;
	new->num = i;
	new->total = total;
	new->flag_l = 0;
	new->flag_r = 0;
	new->flag_dub_r = 0;
	new->flag_dub_l = 0;
	new->flag_q = 0;
	new->flag_dub_q = 0;
	new->cmd = NULL;
	new->cmd_arr = NULL;
	new->f_build_in = 0;;
	new->red = NULL;
	new->check = NULL;
	new->create = NULL;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_front(t_tok **lst, t_tok *new)
{
	new->next = *lst;
	*lst = new;
}

t_tok	*create_token_list(char **arr, int total)
{
	t_tok	*list;
	t_tok	*new_node;
	int		i;

	i = total;
	list = NULL;
	while(i >= 0)
	{
		new_node = create_pipe_part(arr[i], i, total);
		if (new_node == NULL)
			return (NULL);//вернуть ошибку
		ft_lstadd_front(&list, new_node);
		i--;
	}
	return (list);
}

t_redir	*init_red(void)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		return (NULL); //вернуть ошибку
	new->in = NULL;
	new->out = NULL;
	new->type_in = 0;
	new->type_out = 0;
	return (new);
}
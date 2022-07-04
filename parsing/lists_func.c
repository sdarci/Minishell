/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:23:01 by eheike            #+#    #+#             */
/*   Updated: 2022/06/28 19:59:29 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*create_node(void *data, int num_type)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->data = data;
	new->type = num_type;
	new->next = NULL;
	return (new);
}

static t_list	*last_elem(t_list *list)
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

static t_list	*add_to_bildins(char **arr_cmd)
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
	arr_cmd[0] = "echo";
	arr_cmd[1] = "cd";
	arr_cmd[2] = "pwd";
	arr_cmd[3] = "export";
	arr_cmd[4] = "unset";
	arr_cmd[5] = "env";
	arr_cmd[6] = "exit";
	arr_cmd[7] = NULL;
	list_of_bi = add_to_bildins(arr_cmd);
	free (arr_cmd);
	return (list_of_bi);
}

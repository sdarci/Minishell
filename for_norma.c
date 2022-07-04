/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_norma.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <sdarci@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:26:38 by sdarci            #+#    #+#             */
/*   Updated: 2022/06/30 18:24:22 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*for_norma(t_shell *s, char **argv, int argc, char **env)
{
	if (argv[1] != NULL)
		exit(printf("NE NADO PODAVAT' ARGS)))\n"));
	argc = 0;
	s = struct_init();
	s->copy_env = array_2d_dup(env);
	return (s);
}

void	free_red(t_tok	*tmp)
{
	if (tmp->red->in)
		free(tmp->red->in);
	if (tmp->red->out)
		free(tmp->red->out);
	free (tmp->red);
}

void	free_check(t_tok *tmp)
{
	t_list	*tmp2;

	tmp2 = NULL;
	while (tmp->check)
	{
		tmp2 = tmp->check;
		tmp->check = tmp->check->next;
		free (tmp2->data);
		free (tmp2);
	}
}

void	freee(t_tok *tmp)
{
	if (tmp->line)
		free (tmp->line);
	if (tmp->cmd)
		free (tmp->cmd);
	if (tmp->red)
		free_red(tmp);
	if (tmp->check)
		free_check(tmp);
}

void	error_func1(t_shell *shell)
{
	ft_putstr(COLOR_RED, 2);
	ft_putstr("Error with ", 2);
	if (shell->cmd->red->type_out == 1)
		perror(shell->cmd->red->out);
	if (shell->cmd->red->type_out == 2)
		perror(shell->cmd->red->out);
	ft_putstr(COLOR_RESET, 2);
	ms_cmd_argv_free(shell->cmd);
	ms_shell_destroy(shell);
	exit(1);
}

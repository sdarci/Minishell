/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <sdarci@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:27:39 by sdarci            #+#    #+#             */
/*   Updated: 2022/06/30 17:50:00 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr(char *str, int std_var)
{
	int			i;
	static int	len_red;
	static int	len_reset;

	if (str == NULL)
		str = "(null)";
	i = 0;
	while (str[i])
		i++;
	if (!len_red || !len_reset)
	{
		len_red = ft_strlen(COLOR_RED);
		len_reset = ft_strlen(COLOR_RESET);
	}
	if (std_var == 2)
		write(std_var, COLOR_RED, len_red);
	write(std_var, str, i);
	if (std_var == 2)
		write(std_var, COLOR_RESET, len_reset);
}

void	ft_free(void **pointer)
{
	free(*pointer);
	*pointer = NULL;
}

void	ms_cmd_argv_free(t_tok *cmd)
{
	int		i;
	t_tok	*tmp;

	tmp = NULL;
	if (cmd != NULL)
	{
		while (cmd)
		{
			i = -1;
			tmp = cmd;
			if (tmp->cmd_arr)
			{
				while (tmp->cmd_arr[++i] != NULL)
					free (tmp->cmd_arr[i]);
				free (tmp->cmd_arr);
			}
			freee(tmp);
			cmd = cmd->next;
			free (tmp);
		}
	}
}

void	ms_shell_destroy(t_shell *shell)
{
	if (shell->cmd != NULL)
	{
		if (shell->cmd->red != NULL)
		{
			if (shell->cmd->red->in)
				free (shell->cmd->red->in);
			if (shell->cmd->red->out)
				free (shell->cmd->red->out);
		}
	}
	if (shell != NULL)
	{
		if (shell->input != NULL)
			ft_free((void **)&shell->input);
		if (shell->prompt_line != NULL)
			ft_free((void **)&shell->prompt_line);
		ft_free((void **)&shell);
		shell = NULL;
	}
}

void	ms_cmd_execute_command_error(t_shell *shell, int tempfd_stdout)
{
	dup2(tempfd_stdout, 1);
	ft_putstr(COLOR_RED, 2);
	ft_putstr("Command not found: ", 2);
	ft_putstr(shell->cmd->cmd_arr[0], 2);
	ft_putstr("\n", 2);
	ft_putstr(COLOR_RESET, 2);
	ms_cmd_argv_free(shell->cmd);
	ms_shell_destroy(shell);
	exit(1);
}

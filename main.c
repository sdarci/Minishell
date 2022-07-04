/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:58:09 by sdarci            #+#    #+#             */
/*   Updated: 2022/07/01 14:31:26 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_cmds(t_shell *sh)
{
	if (ft_strcmp(sh->cmd->cmd_arr[0], "cd") == 0)
		ms_cmd_execute_cd(sh);
	else if (ft_strcmp(sh->cmd->cmd_arr[0], "exit") == 0)
		ms_cmd_execute_exit(sh);
	else if (ft_strcmp(sh->cmd->cmd_arr[0], "echo") == 0)
		ft_echo(sh);
	else if (ft_strcmp(sh->cmd->cmd_arr[0], "export") == 0)
		ft_export(sh);
	else if (ft_strcmp(sh->cmd->cmd_arr[0], "unset") == 0)
		ft_unset(sh);
	else if (ft_strcmp(sh->cmd->cmd_arr[0], "echo") == 0)
		ft_echo(sh);
	else if (ft_strcmp(sh->cmd->cmd_arr[0], "pwd") == 0)
		ft_pwd(sh);
	else
		ms_cmd_execute_fork(sh);
}

void	msshell_do(t_shell *sh)
{
	t_tok	*tmp;

	tmp = sh->cmd;
	if (sh->cmd == NULL)
		return ;
	if (!ft_strncmp(sh->cmd->cmd_arr[0], "\0", ft_strlen(sh->cmd->cmd_arr[0])))
		return ;
	else if (sh->cmd->next != NULL || sh->cmd->red != NULL)
	{
		ms_cmd_execute_pipe(sh);
	}
	else if (sh->cmd->red == NULL)
		simple_cmds(sh);
	ms_cmd_argv_free(tmp);
	free(sh->input);
}

void	ft_get_status_string(t_shell *shell, int flg)
{
	char	cwd[1000];
	char	*tmp;

	if (shell->prompt_line != NULL)
	{
		free(shell->prompt_line);
		shell->prompt_line = NULL;
	}
	getcwd(cwd, 999);
	shell->prompt_line = ft_strdup(NAME);
	tmp = shell->prompt_line;
	shell->prompt_line = ft_strjoin(shell->prompt_line, cwd);
	free(tmp);
	tmp = shell->prompt_line;
	shell->prompt_line = ft_strjoin(shell->prompt_line, "# ");
	free(tmp);
	if (flg == 0)
		shell->input = readline(shell->prompt_line);
	if (shell->input != NULL)
		add_history(shell->input);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*s;
	int		flag;

	s = NULL;
	s = for_norma(s, argv, argc, env);
	while (1)
	{
		signal(SIGINT, ms_signal_handler);
		signal(SIGTSTP, ms_signal_handler);
		signal(SIGQUIT, ms_signal_handler);
		flag = 0;
		ft_get_status_string(s, 0);
		s->cmd = parse(s->input, s->copy_env, &flag, &(s->status));
		if (flag == 1)
			ms_cmd_execute_exit(s);
		else if (flag == 0)
			msshell_do(s);
		else if (flag == 2)
			free(s->input);
	}
	exit (0);
}

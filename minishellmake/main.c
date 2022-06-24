#include "minishell.h"

void	simple_cmds(t_shell *sh)
{
	pid_t	g;
	int		test;
	
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
	else
	{
		g = fork();
		if (g == 0)
			do_shell_command(sh);
		else
			waitpid(g, &test, WUNTRACED);
	}
	if (sh->cmd != NULL)
	{
		ms_cmd_argv_free(sh->cmd);
	}
}

void	msshell_do(t_shell *sh)
{
	if (!ft_strncmp(sh->cmd->cmd_arr[0], "\0", ft_strlen(sh->cmd->cmd_arr[0])))
		return ;
	else if (sh->cmd->next != NULL || sh->cmd->red != NULL)
	{
		ms_cmd_execute_pipe(sh);
	}
	else if (sh->cmd->red == NULL)
		simple_cmds(sh);
}

void	ft_get_status_string(t_shell *shell)
{
	char	*name;
	char	cwd[1000];

	name = "Minishell";
	if (shell->prompt_line != NULL)
		free(shell->prompt_line);
	shell->prompt_line = (char *)malloc(10000);
	getcwd(cwd, 999);
	ft_strcpy(shell->prompt_name, name);
	ft_strcpy(shell->prompt_line, COLOR_ORANGE);
	ft_memjoin(shell->prompt_line, name);
	ft_memjoin(shell->prompt_line, ":");
	ft_memjoin(shell->prompt_line, COLOR_ORANGE);
	ft_memjoin(shell->prompt_line, cwd);
	ft_memjoin(shell->prompt_line, "# ");
	ft_memjoin(shell->prompt_line, COLOR_ORANGE);
	shell->input = readline(shell->prompt_line);
	add_history(shell->input);
}

t_shell	*struct_init(void)
{
	t_shell	*s;

	s = (t_shell *)malloc(sizeof(t_shell));
	if (!s)
		return (NULL);
	s->input = NULL;
	s->prompt_line = NULL;
	s->prompt_name = NULL;
	s->line = NULL;
	s->heredoc_file = NULL;
	s->fd_her = -1;
	s->status = 0;
	s->env1 = (t_env *)malloc(sizeof(t_env));
	return (s);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	int		flag;

	shell = struct_init();
	argc++;
	argv = NULL;
	shell->prompt_name = (char *)malloc(1000);
	shell->copy_env = array_2d_dup(env);
	while (1)
	{
		flag = 0;
		ft_get_status_string(shell);
		shell->cmd = parse(shell->input, shell->copy_env, &flag, &(shell->status));
		if (flag == 1)
		{
			printf("\nexit\n");
			exit(1);
		}
		else if (flag == 0 && shell->status == 0)
		{
			msshell_do(shell);
			free(shell->input);
			// ms_cmd_argv_free(shell->cmd);
			// ms_shell_destroy(shell);
		}
		else if (flag == 2)
			free(shell->input);
	}
	exit (0);
}

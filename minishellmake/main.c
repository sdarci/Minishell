#include "minishell.h"

static void	ms_cmd_execute_pipe(t_shell *shell)
{
	int		fd[4];

	pipe(fd);
	fd[2] = fd[0];
	fd[3] = fd[1];
	ms_cmd_execute_fork(shell);
	while (shell->cmd->next != NULL)
	{
		close(fd[3]);
		pipe(fd);
		fd[3] = fd[1];
	// ms_cmd_execute_fork(shell);
		shell->cmd = shell->cmd->next;
		ms_cmd_execute_fork(shell);
		close(fd[2]);
		fd[2] = fd[0];
	}
	fd[2] = fd[0];
	close(fd[3]);
	close(fd[2]);
}

void	msshell_do(t_shell *sh)
{
	// if (sh->cmd->next == NULL)
	// 	do_shell_command(sh);
	// if (sh->cmd->next == NULL && sh->cmd->red != NULL)
	// {
	// 	fd_redirect_out(sh);
	// 	fd_redirect_in(sh);
	// 	do_shell_command(sh);
	// }
	if (sh->cmd->next == NULL)
		ms_cmd_execute_fork(sh);
	else
		ms_cmd_execute_pipe(sh);
}


void	ft_get_status_string(t_shell *shell, char *cwd)
{
	char *name;

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
	add_history(shell->input); // добавляет историю
}

t_shell *struct_init(void)
{
	t_shell *s;
	s = (t_shell *)malloc(sizeof(t_shell));
	if (!s)
		return (NULL); //вернуть ошибку памяти
	s->input = NULL;
	s->prompt_line = NULL;
	s->prompt_name = NULL;
	s->line = NULL;
	s->env1 = (t_env *)malloc(sizeof(t_env));
	return(s);
}

int main(int argc, char **argv, char **env)
{
	t_shell *shell;
	char cwd[1000];

	shell = struct_init();
	argc++;
	argv = NULL;
	shell->prompt_name = (char *)malloc(10000);
	shell->copy_env = env;
	while (1)
	{
		ft_get_status_string(shell, cwd);
		shell->cmd = parse(shell->input, env);
		msshell_do(shell);
		free(shell->input);
	}
	return (0);
}
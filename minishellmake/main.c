#include "minishell.h"

void	msshell_do(t_shell *sh)
{
	printf("%d\n", sh->cmd->red->type_out);
	if (sh->cmd->next == NULL && sh->cmd->red == NULL)
		do_shell_command(sh);
	if (sh->cmd->next == NULL && sh->cmd->red != NULL)
		ms_cmd_execute_fd_redirect_out(sh);
		
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
	char *name = "MiniShell";
	char cwd[1000];

	shell = struct_init();
	shell->prompt_name = (char *)malloc(10000);
	shell->copy_env = env;
	// while (ft_strncmp("PATH=", *env, 5) != 0 && *env)
	// 	env++;
	while (1)
	{
		ft_get_status_string(shell, cwd);
		shell->cmd = parse(shell->input, env);
		//exec_buildin(shell, cwd);
		msshell_do(shell);
		//ms_tree_execute(shell);
		free(shell->input);
	}
	return (0);
}
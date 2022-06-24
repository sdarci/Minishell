#include "minishell.h"

void	fd_redirect_out(t_shell *shell)
{
	int	fd;

	fd = 0;
	if (shell->cmd->red != NULL)
	{
		if (shell->cmd->red->type_out == 1 || shell->cmd->red->type_out == 2)
		{
			if (shell->cmd->red->type_out == 1)
				fd = open(shell->cmd->red->out,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (shell->cmd->red->type_out == 2)
				fd = open(shell->cmd->red->out,
						O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (shell->cmd->red->type_in == 4)
			{
				fd = open(shell->cmd->red->out, O_CREAT | O_WRONLY, 0644);
			}
			if (fd == -1)
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
			dup2(fd, 1);
		}
	}
}

void	fd_redirect_in(t_shell *shell)
{
	int	fd;

	fd = 0;
	if (shell->cmd->red != NULL)
	{
		if (shell->cmd->red->type_in == 3 || shell->cmd->red->type_in == 4)
		{
			if (shell->cmd->red->type_in == 3)
			{
				fd = open(shell->cmd->red->in, O_RDONLY);
			}
			if (fd == -1)
			{
				ft_putstr(COLOR_RED, 2);
				ft_putstr("Error with ", 2);
				perror(shell->cmd->red->out);
				ft_putstr(COLOR_RESET, 2);
				ms_cmd_argv_free(shell->cmd);
				ms_shell_destroy(shell);
				exit(1);
			}
			if (dup2(fd, 0) == -1)
				ft_putstr_fd(strerror(errno), 2);
			dup2(fd, 0);
		}	
	}
}

void	ms_write_heredoc_file_readline(t_shell *shell)
{
	char	*str;
	char	*lim;

	str = NULL;
	lim = shell->cmd->red->in;
	printf("%d\n \n ", shell->fd_her);
	while (1)
	{
		str = readline("> ");
		if (str == NULL)
		{
			printf("!!! heredoc razdelen znakom konca faila vmesto «%s»\n",
				shell->cmd->red->in);
			break ;
		}
		if (ft_strcmp(lim, str) == 0)
			break ;
		write(shell->fd_her, str, ft_strlen(str));
		write(shell->fd_her, "\n", 1);
		free(str);
	}
	free(str);
}

void	ms_create_heredoc_file(t_shell *shell)
{
	int		fd;
	char	*filename;

	filename = "del";
	if (shell->cmd->red != NULL)
	{
		if (shell->cmd->red->type_in == 4)
		{
			fd = -1;
			while (fd == -1)
			{
				fd = open(filename, O_CREAT | O_EXCL | O_RDWR, 0644);
			}
			if (shell->heredoc_file != NULL)
			{
				fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
				shell->heredoc_file = NULL;
			}
			shell->fd_her = fd;
			shell->heredoc_file = filename;
			if (shell->cmd->cmd_arr[1] != NULL)
				shell->cmd->cmd_arr[1] = filename;
		}
	}
}

//////////
//чтение хередока
// buf = readline("> ");
// //printf("buf = %s\n", buf);
// while (ft_strncmp(buf, tmp_r->name, ft_strlen(buf)) != 0)
// {
//  if (tmp_r->text == NULL)
//      tmp_r->text = buf;
//  else
//  {
//      fr = tmp_r->text;
//      tmp_r->text = ft_strjoin(tmp_r->text, buf);
//      free(fr);
//  }
//  buf = readline("> ");
// }
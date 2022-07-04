/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <sdarci@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:09:48 by sdarci            #+#    #+#             */
/*   Updated: 2022/06/30 18:32:30 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			{
				fd = open(shell->cmd->red->out,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
			}
			else if (shell->cmd->red->type_out == 2)
				fd = open(shell->cmd->red->out,
						O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				error_func1(shell);
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
				fd = open(shell->cmd->red->in, O_RDONLY);
			if (fd == -1)
			{
				ft_putstr(COLOR_RED, 2);
				ft_putstr("Error with ", 2);
				perror(shell->cmd->red->in);
				ft_putstr(COLOR_RESET, 2);
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

char	**rec_arr(char **arr, char *filename)
{
	char	**tmp;
	int		i;

	i = 0;
	while (arr[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	if (tmp == NULL)
		exit(1);
	i = 0;
	while (arr[i])
	{
		tmp[i] = arr[i];
		i++;
	}
	tmp[i] = ft_strdup(filename);
	if (tmp[i] == NULL)
		exit(1);
	tmp[i + 1] = NULL;
	free(arr);
	return (tmp);
}

void	ms_create_heredoc_file(t_shell *shell)
{
	int		fd;
	char	*filename;

	if (shell->cmd->red != NULL)
	{
		if (shell->cmd->red->out)
			filename = shell->cmd->red->out;
		else
			filename = ".del";
		if (shell->cmd->red->type_in == 4)
		{
			fd = -1;
			while (fd == -1)
				fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (shell->heredoc_file != NULL)
			{
				fd = open(shell->heredoc_file, O_RDWR | \
				O_CREAT | O_TRUNC, 0644);
				shell->heredoc_file = NULL;
			}
			shell->fd_her = fd;
			shell->heredoc_file = filename;
			check_kostl(shell, filename);
		}
	}
}

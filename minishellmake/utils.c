#include "minishell.h"

char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memjoin(void *dst, const void *src)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if ((dst == src) || src_len == 0)
		return (dst);
	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	while (i < src_len)
	{
		((unsigned char *)dst)[dst_len + i] = ((const unsigned char *)src)[i];
		i++;
	}
	((unsigned char *)dst)[dst_len + i] = '\0';
	return (dst);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*p;
	size_t			count_byte;
	size_t			i;

	if (!s)
		return (NULL);
	i = 0;
	if (ft_strlen(s) < start)
		count_byte = 1;
	else if (ft_strlen(s) - start >= len)
		count_byte = (len + 1) * sizeof(char);
	else
		count_byte = (ft_strlen(s) - start + 1) * sizeof(char);
	p = malloc(count_byte);
	if (p == NULL)
		return (NULL);
	while (i < len && s[start + i] != '\0' && ft_strlen(s) >= start)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	ft_puterror(t_shell *shell, int code, char *name)
{
	ft_putstr("Error: ", 2);
	if (code == 1)
		ft_putstr("Programmu neobhodimo zapuskat bez parametrov\n", 2);
	if (code == 2)
	{
		ft_putstr("Ne udalos vydelit pamyat. ", 2);
		ft_putstr(name, 2);
	}
	if (code == 3)
		ft_putstr("excve\n", 2);
	if (code == 4)
	{
		ft_putstr("incorrect variable. ", 2);
		ft_putstr(name, 2);
	}
	//ms_shell_destroy(shell);
	exit(1);
}

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
	ft_free((void **)&cmd->cmd_arr);
}

void	ms_shell_destroy(t_shell *shell)
{
	if (shell != NULL)
	{
		if (shell->input != NULL)
			ft_free((void **)&shell->input);
		if (shell->prompt_name != NULL)
			ft_free((void **)&shell->prompt_name);
		if (shell->prompt_line != NULL)
			ft_free((void **)&shell->prompt_line);
		// if (shell->lexerlist != NULL)
		// 	ms_lexerlist_destroy(shell);
		// if (shell->lexertree != NULL)
		// 	ms_parse_tree_destroy(shell);
		// if (shell->trlist != NULL)
		// 	ms_trlist_destroy(shell);
		if (shell->cmd != NULL)
			ft_free((void **)&shell->cmd);
		// ft_arrayfree((void ***)&shell->envp, shell->env_size);
		// ft_free((void **)&shell->st);
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








char	**malloc_ch_ch(size_t size)
{
	char	**p;

	p = malloc(size);
	if (p == NULL)
		exit(1);
	return (p);
}

size_t	len_2d_array(char **string)
{
	size_t	i;

	i = 0;
	if (string == NULL)
		return (0);
	while (string[i] != NULL)
		i++;
	return (i);
}

char	**array_2d_dup(char **array)
{
	char	**duplicate;
	size_t	i;

	i = 0;
	duplicate = malloc_ch_ch(sizeof(char *) * (len_2d_array(array) + 2));
	while (i < len_2d_array(array))
	{
		duplicate[i] = ft_strdup(array[i]);
		i++;
	}
	duplicate[i] = NULL;
	return (duplicate);
}
#include "minishell.h"

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

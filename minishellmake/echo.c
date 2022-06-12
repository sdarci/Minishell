#include "minishell.h"

void	ft_echo(t_shell *s)
{
	int		i;
	char	*str;

	i = 0;
	while(s->input[i] != '\0')
	{
		i++;	
	}
	write(1, s->input ,i);
	write(1, "\n" ,1);
}
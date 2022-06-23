#include "minishell.h"

void	ft_echo(t_shell *s)
{
	int		i;


	i = 0;
	if (s->cmd->cmd_arr[1] == NULL) 
	{
		while(s->input[i] != '\0')
		{
			i++;	
		}
		write(1, s->input + 5 ,i - 5 );
		write(1, "\n" ,1);
	}
	if (ft_strcmp(s->cmd->cmd_arr[1], "-n") != 0)
	{
		write(1, s->cmd->cmd_arr[1] ,ft_strlen(s->cmd->cmd_arr[1]));
		write(1, "\n" ,1);
	}
	else
		write(1, s->cmd->cmd_arr[2],ft_strlen(s->cmd->cmd_arr[2]));
}
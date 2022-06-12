#include "minishell.h"

char *ft_parse_value(char *argv)
{
	int i;
	int flg;
	char *line;

	i = 0;
	flg = 0;

	while (argv[i] != '=')
		i++;
	flg = i;
	while (argv[i])
		i++;
	line = (char *)malloc(sizeof(char) * (i - flg + 1));
	i = flg;
	i = 0;
	while (argv[flg++])
	{
		line[i] = argv[flg];
		i++;
	}
	line[i] = '\0';
	return(line);
}

char *ft_parse_key(char *argv)
{
	int	i;

	i = 0;
	char *line;

	while (argv[i] != '=')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (argv[i] != '=')
	{
		line[i] = argv[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

struct env1	*env_list(int argc, char **argv, char **env)
{
	
	struct env1 *env1;
	struct env1 *temp, *p;
	int i;

	i = 0;
	env1 = (struct env1 *)malloc(sizeof(struct env1));
	if (!env1)
		return(NULL);
	env1->key = ft_parse_key(env[i]);
	env1->value = ft_parse_value(env[i]);
	env1->next = NULL;
	while (env[++i] != NULL)
	{
		temp = (struct env1 *)malloc(sizeof(struct env1));
		p = env1->next;
		temp->key = ft_parse_key(env[i]);
		temp->value = ft_parse_value(env[i]);
		temp->next = p;
		env1->next = temp;
	}
	return (env1);
}
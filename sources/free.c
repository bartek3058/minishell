#include "../includes/minishell.h"

void	free_args(char **args)
{
	int i;

	i = 0;
	if (args == NULL)
		return ;
	while(*args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}